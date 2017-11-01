//
//  game.cpp
//  Scrabble Game
//

#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>

#include "game.h"
#include "game_state.h"
#include "texture_manager.h"
#include "ResourcePath.hpp"


Game::Game()
{
    this->loadTextures();
    
    this->window.create(sf::VideoMode(1141, 1259 + 125 + 40), "Scrabble Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);
    this->background.setTexture(this->texmgr.getRef("background"));
    this->dock.setTexture(this->texmgr.getRef("dock"));
    this->dock.setOrigin(240, 47);
    this->dock.setPosition(19 + 74.25 * 3, 1220);
    this->dock.scale(.48, .48);
    tile_display = new TileDisplay(this->texmgr.getRef("tile_tex"));
    
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "scrabble-board.jpg"))
        exit( EXIT_FAILURE);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
}

void Game::loadTextures()
{
    texmgr.loadTexture("background", resourcePath() + "scrabble-board.jpg");
    texmgr.loadTexture("tile_tex", resourcePath() + "Scrabble_Letters.jpg");
    texmgr.loadTexture("dock", resourcePath() + "scrabble-tile-dock2.png");
    
}

Game::~Game()
{
    while(!this->states.empty())
        popState();
    delete tile_display;
}

void Game::pushState(GameState* state)
{
    this->states.push(state);
    return;
    
}

void Game::popState()
{
    //delete this->states.top();
    this->states.pop();
}

void Game::changeState(GameState* state)
{
    if (!this->states.empty())
        popState();
    pushState(state);
}

GameState* Game::peekState()
{
    if (this->states.empty())
        return nullptr;
    return this->states.top();
}

void Game::gameLoop()
{
    sf::Clock clock;
    
    while (this->window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();
        
        if (peekState() != nullptr) {
            peekState()->handleInput();
            peekState()->update(dt);
            
            this->window.clear(sf::Color::Black);
            peekState()->draw(dt);
            this->window.display();
        }
    }
}










