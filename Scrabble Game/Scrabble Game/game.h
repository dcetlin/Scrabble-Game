//
//  game.h
//  Scrabble Game

#ifndef GAME_H
#define GAME_H

#include <stack>
#include <SFML/Graphics.hpp>
#include "texture_manager.h"
#include <tile_display.h>


class GameState;

class Game {
    public:
    
    Game();
    ~Game();
    
    std::stack<GameState*> states;
    
    sf::RenderWindow window;
    TextureManager texmgr;
    sf::Sprite background;
    TileDisplay* tile_display;
    
    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();
    
    void gameLoop();
    
    private:
    
    void loadTextures();
};

#endif
