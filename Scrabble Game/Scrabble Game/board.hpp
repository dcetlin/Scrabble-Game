//
//  board.hpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 10/31/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include "pixel_data.h"
#include <SFML/Graphics.hpp>

class Board {
    const char EMPTY = '!';
    const char BLANK_TILE = '_';
    
    enum Multi {NONE, TRIP_WORD, TRIP_LET, DOUB_WORD, DOUB_LET};
    
private:
    char game_board[15][15];
    char tile_dock[7];
    Multi getMultiplier(int x, int y);
    
public:
    Board();
    void getBoardTile(const sf::Vector2i& mouse_position, sf::IntRect& rect);
    
    
};

#endif /* board_hpp */
