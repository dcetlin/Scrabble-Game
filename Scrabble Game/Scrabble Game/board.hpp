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
#include "tile_display.h"
#include <SFML/Graphics.hpp>

const char BLANK_TILE = '_';

class Board {
    const char EMPTY = '!';
    enum Multi {NONE, TRIP_WORD, TRIP_LET, DOUB_WORD, DOUB_LET};
    
private:
    struct TileData {
        TileDisplay::Tile* tile;
        sf::Vector2i coords;
        char ch;
        
        TileData(TileDisplay::Tile* t, sf::Vector2i v, char c) : tile(t), coords(v), ch(c){}
    };
    
    std::vector<TileData> placed_tiles;
    
    char game_board[15][15];
    char tile_dock[7];
    char* last_char;
    Multi getMultiplier(sf::Vector2i board_pos);
    
    void move_placed_tiles_to_dock();
    
    inline void order_palced_tiles_by_x();
    inline void order_palced_tiles_by_y();
    inline bool validate_vertical(int coordchecker_const);
    inline bool validate_horizontal(int coordchecker_const);
    
    void debug_print();
    
public:
    
    Board();
    Board(const Board& b);
    void getBoardTile(const sf::Vector2i& mouse_position, sf::IntRect& rect, sf::Vector2i& board_pos, int& rack_pos, bool justclickd);
    void getBoardTile(const sf::Vector2i& mouse_position, sf::IntRect& rect);
    
    bool update_board(sf::Vector2i board_pos, int rack_pos, char ch, bool isdrag, TileDisplay::Tile* tile_d);
    
    std::vector<int> getAllEmptyRackCoords();
    sf::Vector2i getRackCoords(int x);
    sf::Vector2i getBoardCoords(sf::Vector2i coords);
    bool validateBoard();
    bool validateBoard_FirstMove();
    
    
    

};

#endif /* board_hpp */
