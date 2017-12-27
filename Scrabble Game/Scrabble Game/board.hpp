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
    const char BLANK_TILE = ' ';
    
    enum Multi {NONE, TRIP_WORD, TRIP_LET, DOUB_WORD, DOUB_LET};
    
private:
    char game_board[15][15];
    char tile_dock[7];
    char* last_char;
    Multi getMultiplier(sf::Vector2i board_pos);
    void debug_print();
    
public:
    Board();
    void getBoardTile(const sf::Vector2i& mouse_position, sf::IntRect& rect, sf::Vector2i& board_pos, int& rack_pos, bool justclickd);
    void getBoardTile(const sf::Vector2i& mouse_position, sf::IntRect& rect);
    bool update_board(sf::Vector2i board_pos, int rack_pos, char ch);
};

#endif /* board_hpp */
