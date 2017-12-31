//
//  tile_manager.cpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 12/29/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#include "tile_manager.hpp"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int myrandom (int i) { return std::rand()%i;}

TileManager::TileManager(Board* b, TileDisplay* t)
{
    game_board = b;
    td = t;
    
    for (int k = 0; k < 12; k++)
        remaining_tiles.push_back('e');
    for (int k = 0; k < 9; k++) {
        remaining_tiles.push_back('a');
        remaining_tiles.push_back('i');
    } for (int k = 0; k < 8; k++) {
        remaining_tiles.push_back('o');
        remaining_tiles.push_back('o');
    } for (int k = 0; k < 6; k++) {
        remaining_tiles.push_back('n');
        remaining_tiles.push_back('r');
        remaining_tiles.push_back('t');
    } for (int k = 0; k < 4; k++) {
        remaining_tiles.push_back('l');
        remaining_tiles.push_back('s');
        remaining_tiles.push_back('u');
        remaining_tiles.push_back('d');
    } for (int k = 0; k < 3; k++) {
        remaining_tiles.push_back('g');
    } for (int k = 0; k < 2; k++) {
        remaining_tiles.push_back('b');
        remaining_tiles.push_back('c');
        remaining_tiles.push_back('m');
        remaining_tiles.push_back('p');
        remaining_tiles.push_back('f');
        remaining_tiles.push_back('h');
        remaining_tiles.push_back('v');
        remaining_tiles.push_back('w');
        remaining_tiles.push_back('y');
        remaining_tiles.push_back(BLANK_TILE);
    }
    remaining_tiles.push_back('k');
    remaining_tiles.push_back('j');
    remaining_tiles.push_back('x');
    remaining_tiles.push_back('q');
    remaining_tiles.push_back('z');
    
    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle(remaining_tiles.begin(), remaining_tiles.end(), myrandom);
    
//    printf("{");
//    for (char c : remaining_tiles)
//        printf("%c ", c);
//    printf("}\n");
}

bool TileManager::createTileAt(sf::Vector2i coords, int rack_pos, char ch)
{
    if (!game_board->update_board(coords, rack_pos, ch, false, nullptr))
        return false;
    sf::Vector2i location = (rack_pos == -1)? game_board->getBoardCoords(coords): game_board->getRackCoords(rack_pos);
    td->newTile(ch, location.x, location.y);
    return true;
}

void TileManager::fillRack()
{
    //std::vector<sf::Vector2i> v = game_board->getAllEmptyRackCoords();
    for (int index : game_board->getAllEmptyRackCoords()) {
        char c = remaining_tiles.back(); remaining_tiles.pop_back();
        game_board->update_board({-1,-1}, index, c, false, nullptr);
        sf::Vector2i v = game_board->getRackCoords(index);
        td->newTile(c, v.x, v.y);
    }
    printf("\n");
}
