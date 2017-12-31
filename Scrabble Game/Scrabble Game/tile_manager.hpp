//
//  tile_manager.hpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 12/29/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#ifndef tile_manager_hpp
#define tile_manager_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "tile_display.h"

class TileManager {

public:
    TileManager(Board* b, TileDisplay* t);
    bool createTileAt(sf::Vector2i coords, int rack_pos, char ch);
    void fillRack();

private:
    Board* game_board;
    TileDisplay* td;
    std::vector<char> remaining_tiles;
};

#endif /* tile_manager_hpp */
