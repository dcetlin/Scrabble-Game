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

#define DEBUG false

GameStateEditor::GameStateEditor(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
    
    if (true) {
        sf::Font font;
        
        //font.loadFromFile(resourcePath() + "Times.ttf");
        _mouse.setFont(font);
        _mouse.setCharacterSize(200);
        _mouse.setFillColor(sf::Color::Red);
        _mouse.setPosition(50, 50);
    }
    
    is_being_dragged = nullptr;
    
    tile_outline.setSize(sf::Vector2f(TILE_BOX_WIDTH, TILE_BOX_HEIGHT));
    tile_outline.setOutlineColor(sf::Color::Yellow);
    tile_outline.setFillColor(sf::Color::Transparent);
    tile_outline.setOutlineThickness(.85);
    
    tile_outline_view = false;
    
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
    game->tile_display->display_tiles(this->game->window);
    
    if (tile_outline_view)
        game->window.draw(tile_outline);
    
    if (DEBUG) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(game->window);
        std::string s = "[" + std::to_string(mouse_position.x) + ":" + std::to_string(mouse_position.y) + "]";
        _mouse.setString(s);
        game->window.draw(_mouse);
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
                    for (TileDisplay::Tile t : game->tile_display->visible_tiles) {
                        sf::Sprite* s = t.sprite;
                        if (s->getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                            is_being_dragged = s;
                            is_being_dragged->setScale(.4, .4);
                            game->tile_display->move_to_last(s);
                            break;
                        }
                    }
                    
                }
            }
            default: break;
        }
        if (is_being_dragged != nullptr) {
            
            sf::IntRect highlight_tile;
            game_board.getBoardTile(mouse_position, highlight_tile);
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                is_being_dragged->setPosition(mouse_position.x - OFFSET.x, mouse_position.y - OFFSET.y);
                
                tile_outline.setPosition(highlight_tile.left, highlight_tile.top);
                tile_outline_view = true;
                
            } else {
                is_being_dragged->setScale(.2422, .2437);
                is_being_dragged->setPosition(highlight_tile.left, highlight_tile.top);
                is_being_dragged = nullptr;
                tile_outline_view = false;
            }
        }
    }
    
    return;
}




