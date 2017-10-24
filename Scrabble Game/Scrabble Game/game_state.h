//
//  game_state.h
//  Scrabble Game


#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game.h"

//Virtual class
class GameState {
    
    public:
    
    Game* game;
    
    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;
    
};

#endif
