//
//  game_state_editor.cpp
//  Scrabble Game
//


#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "game_state_editor.h"
#include "tile_display.h"
#include "ResourcePath.hpp"
#include <vector>
#include <iostream>

#define DEBUG true

GameStateEditor::GameStateEditor(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
    
    if (DEBUG) {
        sf::Font font;
        
        const std::string filepath = resourcePath() + "arial.ttf";
        if (!font.loadFromFile(filepath)) {
            fprintf(stderr, "Unable to load font\n");
            exit(1);
        }
        _mouse.setFont(font);
        _mouse.setCharacterSize(200);
        _mouse.setFillColor(sf::Color::Red);
        _mouse.setPosition(50, 50);
    }
    
    is_being_dragged = nullptr;
    last_position = {0, 0};
    
    tile_outline.setSize(sf::Vector2f(TILE_BOX_WIDTH, TILE_BOX_HEIGHT));
    tile_outline.setOutlineColor(sf::Color::Yellow);
    tile_outline.setFillColor(sf::Color::Transparent);
    tile_outline.setOutlineThickness(.85);
    
    tile_outline_view = false;
    button_isclicked = false;
    
        sf::IntRect irect;
        game_board.getBoardTile({400, 600}, irect);
        game->tile_display->newTile('z', irect.left, irect.top);

        game_board.getBoardTile({600, 800}, irect);
        game->tile_display->newTile(' ', irect.left, irect.top);
    
        game_board.getBoardTile({1100, 300}, irect);
        game->tile_display->newTile('m', irect.left, irect.top);
    
        game_board.getBoardTile({500, 500}, irect);
        game->tile_display->newTile('o', irect.left, irect.top);
    
        game_board.getBoardTile({1500, 1500}, irect);
        game->tile_display->newTile('p', irect.left, irect.top);
}

void GameStateEditor::draw(const float dt)
{
    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->game->background);
    this->game->window.draw(this->game->dock);
    //this->game->window.draw(this->game->submit_button);
    game->tile_display->display_tiles(this->game->window);
    game->button->draw_button(this->game->window);
    
    if (tile_outline_view)
        game->window.draw(tile_outline);
    
    if (DEBUG) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(game->window);
        std::string s = "[" + std::to_string(mouse_position.x) + ":" + std::to_string(mouse_position.y) + "]";
        _mouse.setString(s);
        //game->window.draw(_mouse);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            fprintf(stderr, "%s\n", s.c_str());
    }
    return;
}

void GameStateEditor::update(const float dt)
{
    (void) dt;
}

void GameStateEditor::handleInput()
{
    sf::Event event;
    sf::Vector2i mouse_position;
    bool tile_justclicked = false;
    
    while(this->game->window.pollEvent(event))
    {
        mouse_position = sf::Mouse::getPosition(game->window);
        switch(event.type)
        {
                /* Close the window */
            case sf::Event::Closed:
            {
                this->game->window.close();
                break;
            }
            
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left && is_being_dragged == nullptr) {
                    if (game->button->checkInitialClick(mouse_position)) {
                        button_isclicked = true;
                    } else {
                        for (TileDisplay::Tile* t : game->tile_display->visible_tiles) {
                            sf::Sprite* s = t->sprite;
                            if (s->getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                                last_position = {(int) s->getPosition().x, (int) s->getPosition().y};
                                is_being_dragged = t;
                                is_being_dragged->sprite->setScale(.4, .4);
                                game->tile_display->move_to_last(s);
                                tile_justclicked = true;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (button_isclicked) {
                    button_isclicked = false;
                    if (game->button->checkReleaseClick(mouse_position)) {
                        printf("button was pressed\n");
                    } 
                }
                break;
            }
            default: break;
        }
        if (is_being_dragged != nullptr) {
            
            sf::IntRect highlight_tile;
            sf::Vector2i board_pos = {-1, -1};
            int rack_pos = -1;
            game_board.getBoardTile(mouse_position, highlight_tile, board_pos, rack_pos, tile_justclicked);
            tile_justclicked = false;
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                is_being_dragged->sprite->setPosition(mouse_position.x - OFFSET.x, mouse_position.y - OFFSET.y);
                
                tile_outline.setPosition(highlight_tile.left, highlight_tile.top);
                tile_outline_view = true;
                
            } else {
                is_being_dragged->sprite->setScale(.2422, .2437);
                if (game_board.update_board(board_pos, rack_pos, is_being_dragged->ch)) {
                    is_being_dragged->sprite->setPosition(highlight_tile.left, highlight_tile.top);
                } else {
                    is_being_dragged->sprite->setPosition(last_position.x, last_position.y);
                }
                
                is_being_dragged = nullptr;
                tile_outline_view = false;
            }
        }
        //printf("%s\n", (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))? "left ispressed": "left isnotpressed");
    }
    return;
}
