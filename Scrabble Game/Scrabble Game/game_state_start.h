//
//  GameStateStart.hpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 9/2/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include "game_state.h"

class GameStateStart : public GameState
{
private:
    
    sf::View view;
    
    void loadgame();
    
public:
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
    GameStateStart(Game* game);
};

#endif
