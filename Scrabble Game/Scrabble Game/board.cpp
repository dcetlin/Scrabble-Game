//
//  board.cpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 10/31/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#include "board.hpp"
#include <stdio.h>

#define DELETE_TILE_IF_FOUND(TILE_D, TILES) do {                                                                \
        for (std::vector<TileData>::iterator iter = TILES.begin(); iter != TILES.end(); iter++) {               \
            if (iter->tile == TILE_D) {                                                                         \
                TILES.erase(iter);                                                                              \
                break;                                                                                          \
            }                                                                                                   \
        }                                                                                                       \
    } while(0)

Board::Board()
{
    for (int r = 0; r < 15; r++) {
        for (int c = 0; c < 15; c++) {
            game_board[r][c] = EMPTY;
        }
    }
    for (int k = 0; k < 7; k++)
        tile_dock[k] = EMPTY;
    
    last_char = nullptr;
}

void Board::getBoardTile(const sf::Vector2i& mouse_position, sf::IntRect& rect, sf::Vector2i& board_pos, int& rack_pos, bool justclicked)
{
    double x = mouse_position.x, y = mouse_position.y;
    
    if (x < 0)
        x = 0;
    else if (x > 14 * TILE_BOX_WIDTH + TILE_BOX_INDENT)
        x = 14 * TILE_BOX_WIDTH + TILE_BOX_INDENT;
    if (y < 0)
        y = 0;
    if (y > 16 * TILE_BOX_WIDTH + TILE_BOX_INDENT) {
        if ((x > 4 * TILE_BOX_WIDTH + TILE_BOX_INDENT && x < 11 * TILE_BOX_WIDTH + TILE_BOX_INDENT)
            && (y > 1220 + 70 && y < 1220 + 70 + TILE_BOX_HEIGHT)) {
            rect.left = (int) ((x - TILE_BOX_INDENT) / TILE_BOX_WIDTH) * TILE_BOX_WIDTH + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_WIDTH) / 2;
            rect.top = 1220 + TILE_BOX_INDENT + 50 + (TILE_BOX_WIDTH - TILE_WIDTH) / 2;
            rect.height = (int) TILE_BOX_HEIGHT;
            rect.width = (int) TILE_BOX_WIDTH;
            rack_pos = (rect.left - (4 * TILE_BOX_WIDTH + TILE_BOX_INDENT)) / TILE_BOX_WIDTH;
            
            if (justclicked)
                last_char = tile_dock + rack_pos;
            
            return;
        }
        else
            y = 14 * TILE_BOX_HEIGHT + TILE_BOX_INDENT;
    }
    
    rect.left = (int) ((x - TILE_BOX_INDENT) / TILE_BOX_WIDTH) * TILE_BOX_WIDTH + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_HEIGHT) / 2;
    rect.top = (int)((y - TILE_BOX_INDENT) / TILE_BOX_HEIGHT) * TILE_BOX_HEIGHT + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_WIDTH) / 2;
    rect.height = (int) TILE_BOX_HEIGHT;
    rect.width = (int) TILE_BOX_WIDTH;
    
    board_pos.x = (rect.left) / TILE_BOX_WIDTH;
    board_pos.y = (rect.top - TILE_BOX_INDENT) / TILE_BOX_HEIGHT;
    
    if (justclicked)
        last_char = &game_board[board_pos.x][board_pos.y];
}

void Board::getBoardTile(const sf::Vector2i& mouse_position, sf::IntRect& rect)
{
    double x = mouse_position.x, y = mouse_position.y;
    
    if (x < 0)
        x = 0;
    else if (x > 14 * TILE_BOX_WIDTH + TILE_BOX_INDENT)
        x = 14 * TILE_BOX_WIDTH + TILE_BOX_INDENT;
    if (y < 0)
        y = 0;
    if (y > 15 * TILE_BOX_WIDTH + TILE_BOX_INDENT) {
        if ((x > 4 * TILE_BOX_WIDTH + TILE_BOX_INDENT && x < 11 * TILE_BOX_WIDTH + TILE_BOX_INDENT)
            && (y > 1220 + 50 && y < 1220 + 50 +  TILE_BOX_HEIGHT)) {
            rect.left = (int) (x / TILE_BOX_WIDTH) * TILE_BOX_WIDTH + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_HEIGHT) / 2;
            rect.top = 1220 + TILE_BOX_INDENT + 50 + (TILE_BOX_WIDTH - TILE_WIDTH) / 2;
            rect.height = (int) TILE_BOX_HEIGHT;
            rect.width = (int) TILE_BOX_WIDTH;
            return;
        }
        else
            y = 14 * TILE_BOX_HEIGHT + TILE_BOX_INDENT;
    }
    
    rect.left = (int) (x / TILE_BOX_WIDTH) * TILE_BOX_WIDTH + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_HEIGHT) / 2;
    rect.top = (int)(y / TILE_BOX_HEIGHT) * TILE_BOX_HEIGHT + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_WIDTH) / 2;
    rect.height = (int) TILE_BOX_HEIGHT;
    rect.width = (int) TILE_BOX_WIDTH;
}

Board::Multi Board::getMultiplier(sf::Vector2i board_pos)
{
    int x = board_pos.x;
    int y = board_pos.y;
    if (((x == 0 || x == 14) and (y == 0 || y == 7 || y == 14))
        or ((x == 7) and (y == 0 || y == 14))) {
        printf("Triple Word\n");
        return Board::Multi::TRIP_WORD;
    } else if ((((x == y) || (x == 14 - y)) and ((x >= 1 && x <= 4) || (x == 7) || (x >= 10 && x <= 14)))) {
        printf("Double Word\n");
        return Board::Multi::DOUB_WORD;
    } else if (((x == 1 || x == 13) and (y == 5 || y == 9))
               or ((x == 5 || x == 9) and (y == 1 || y == 5 || y == 9 || y == 13))) {
        printf("Triple Letter\n");
        return Board::Multi::TRIP_LET;
    } else if (((x == 0 || y == 0 || x == 14 || y == 14) && (x == 3 || x == 11 || y == 3 || y == 11))
             or ((x == 2 || y == 2 || x == 12 || y == 12) && (x == 6 || y == 6 || x == 8 || y == 8))
             or ((x == 3 || y == 3 || x == 11 || y == 11) && (x == 7 || y == 7))
               or ((y == 6 || y == 8) && (x == 6 || x == 8))) {
        printf("Double Letter\n");
        return Board::Multi::DOUB_LET;
    } else {
        printf("No Mult\n");
        return Board::Multi::NONE;
    }
}

//TODO make two update boards...
bool Board::update_board(sf::Vector2i board_pos, int rack_pos, char ch, bool isdrag, TileDisplay::Tile* tile_d)
{
    if (rack_pos == -1) {
        if (game_board[board_pos.x][board_pos.y] != EMPTY)
            return false;
        game_board[board_pos.x][board_pos.y] = ch;
        
        if (tile_d != nullptr) {
            DELETE_TILE_IF_FOUND(tile_d, placed_tiles);
            TileData td(tile_d, board_pos, ch);
            placed_tiles.push_back(td);
        }
    } else {
        if (tile_dock[rack_pos] != EMPTY)
            return false;
        tile_dock[rack_pos] = ch;
        
        if (tile_d != nullptr) {
            DELETE_TILE_IF_FOUND(tile_d, placed_tiles);
        }
    }
    
    if (isdrag && last_char != nullptr)
        *last_char = EMPTY;
    
    debug_print();
    return true;
}

sf::Vector2i Board::getRackCoords(int x)
{
    return sf::Vector2i{static_cast<int>(317 + x * TILE_BOX_WIDTH), 1290};
}

sf::Vector2i Board::getBoardCoords(sf::Vector2i coords)
{
    return sf::Vector2i {static_cast<int>(coords.x * TILE_BOX_WIDTH + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_HEIGHT) / 2), static_cast<int>(coords.y * TILE_BOX_HEIGHT + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_WIDTH) / 2)};
}

std::vector<int> Board::getAllEmptyRackCoords()
{
    std::vector<int> v;
    for (int k = 0; k < 7; k++) {
        if (tile_dock[k] == EMPTY)
            v.push_back(k);
    }
    return v;
}

#define EXIT_FAIL move_placed_tiles_to_dock(); placed_tiles.clear(); return false
#define EXIT_SUCCEED placed_tiles.clear(); return true
bool Board::validateBoard()
{
    std::string word = "";
    size_t num_used = placed_tiles.size();
    
    if (num_used > 1) {
        int coordchecker_const;
        if ((coordchecker_const = placed_tiles[0].coords.x) == placed_tiles[1].coords.x) { //Check Vertical
            return validate_vertical(coordchecker_const);
        } else if ((coordchecker_const = placed_tiles[0].coords.y) == placed_tiles[1].coords.y) {
            return validate_horizontal(coordchecker_const);
        } else {
            EXIT_FAIL;
        }
        EXIT_SUCCEED;
    } else if (num_used == 1) {
        #define GB_AT(X_PLUS, YPLUS) game_board[placed_tiles[0].coords.x + X_PLUS][placed_tiles[0].coords.y + YPLUS]
        if (GB_AT(0, 1) != EMPTY || GB_AT(1, 0) != EMPTY || GB_AT(0, -1) != EMPTY || GB_AT(-1, 0) != EMPTY) {
            EXIT_SUCCEED;
        #undef GB_AT
        }
    }
    EXIT_FAIL;
}

inline bool Board::validate_vertical(int coordchecker_const)
{
    std::string word = "";
    char curr_char;
    size_t num_used = placed_tiles.size();
    bool isConnected = false;
    order_palced_tiles_by_y();
    int last_y = placed_tiles[0].coords.y;
    int curr_y = last_y;
    
    for (size_t k = 0; k < num_used; k++, curr_y++) {
        sf::Vector2i curr_coords = placed_tiles[k].coords;
        while (curr_y < curr_coords.y) {
            if ((curr_char = game_board[coordchecker_const][curr_y++]) == EMPTY) {EXIT_FAIL;}
            isConnected = true;
            word += curr_char; //add letters to word
        }
        if (curr_coords.x != coordchecker_const) {EXIT_FAIL;}
        
        if (!isConnected && ((curr_coords.y < 14 && game_board[curr_coords.x][curr_coords.y + 1] != EMPTY) ||
                             (curr_coords.y > 0 && game_board[curr_coords.x][curr_coords.y - 1] != EMPTY)))
            isConnected = true; //Sideword (get rid of first !isConnected)
        word += placed_tiles[k].ch;
    }
    
    while (curr_y < 15 && (curr_char = game_board[coordchecker_const][curr_y++]) != EMPTY) {
        isConnected = true;
        word += curr_char;
    }
    
    while (--last_y >= 0 && (curr_char = game_board[coordchecker_const][last_y]) != EMPTY) {
        isConnected = true;
        word += curr_char;
    }
    if (!isConnected) {EXIT_FAIL;}
    else {printf("Vertical Word: %s\n", word.c_str()); EXIT_SUCCEED;}
}

inline bool Board::validate_horizontal(int coordchecker_const)
{
    std::string word = "";
    char curr_char;
    size_t num_used = placed_tiles.size();
    bool isConnected = false;
    
    order_palced_tiles_by_x();
    int last_x = placed_tiles[0].coords.x;
    int curr_x = last_x;
    
    for (size_t k = 0; k < num_used; k++, curr_x++) {
        sf::Vector2i curr_coords = placed_tiles[k].coords;
        while (curr_x < curr_coords.x) {
            if ((curr_char = game_board[curr_x++][coordchecker_const]) == EMPTY) {EXIT_FAIL;}
            isConnected = true;
            word += curr_char; //add letters to word
        }
        if (curr_coords.y != coordchecker_const) {EXIT_FAIL;}
        
        if (!isConnected && ((curr_coords.y < 14 && game_board[curr_coords.x][curr_coords.y + 1] != EMPTY) ||
                             (curr_coords.y > 0 && game_board[curr_coords.x][curr_coords.y - 1] != EMPTY)))
            isConnected = true;
        
        word += placed_tiles[k].ch;
    }
    
    while (curr_x < 15 && (curr_char = game_board[curr_x++][coordchecker_const]) != EMPTY) {
        isConnected = true;
        word += curr_char;
    }
    
    while (--last_x >= 0 && (curr_char = game_board[last_x][coordchecker_const]) != EMPTY) {
        isConnected = true;
        word += curr_char;
    }
    
    if (!isConnected) {EXIT_FAIL;}
    else {printf("Horizontal Word: %s\n", word.c_str()); EXIT_SUCCEED;}
}

bool Board::validateBoard_FirstMove()
{
    std::string word = "";
    char curr_char;
    
    size_t num_used = placed_tiles.size();
    if (num_used > 1) {
        bool isConnected = false;
        int coordchecker_const;
        if ((coordchecker_const = placed_tiles[0].coords.x) == placed_tiles[1].coords.x) { //Check Vertical
            
            order_palced_tiles_by_y();
            
            for (size_t k = 0; k < num_used; k++) {
                sf::Vector2i curr_coords = placed_tiles[k].coords;
                if ((curr_char = game_board[curr_coords.x][curr_coords.y]) == EMPTY) {EXIT_FAIL;}
                if (placed_tiles[k].coords.x != coordchecker_const) {EXIT_FAIL;}
                if (placed_tiles[k].coords.y == 7 && placed_tiles[k].coords.x == 7) {isConnected = true;}
                word += placed_tiles[k].ch;
            }
            
            if (!isConnected) {EXIT_FAIL;}
            printf("Vertical Word: %s\n", word.c_str());
            EXIT_SUCCEED;
            
        } else if ((coordchecker_const = placed_tiles[0].coords.y) == placed_tiles[1].coords.y) {
            order_palced_tiles_by_x();
            
            for (size_t k = 0; k < num_used; k++) {
                sf::Vector2i curr_coords = placed_tiles[k].coords;
                if ((curr_char = game_board[curr_coords.x][curr_coords.y]) == EMPTY) {EXIT_FAIL;}
                if (placed_tiles[k].coords.y != coordchecker_const) {EXIT_FAIL;}
                if (placed_tiles[k].coords.x == 7 && coordchecker_const == 7) {isConnected = true;}
                word += placed_tiles[k].ch;
            }
            
            if (!isConnected) {EXIT_FAIL;}
            printf("Vertical Word: %s\n", word.c_str());
            EXIT_SUCCEED;
        } else {
            EXIT_FAIL;
        }
    }
    EXIT_FAIL;
}
#undef EXIT_FAIL
#undef EXIT_SUCCEED

void Board::move_placed_tiles_to_dock()
{
    int curr_open_in_dock = 0;
    for (TileData t : placed_tiles) {
        while (tile_dock[curr_open_in_dock] != EMPTY) {curr_open_in_dock++;}
        t.tile->sprite->setPosition((sf::Vector2f)getRackCoords(curr_open_in_dock));
        game_board[t.coords.x][t.coords.y] = EMPTY;
        tile_dock[curr_open_in_dock] = t.ch;
    }
}

inline void Board::order_palced_tiles_by_x() {
    int i, j;
    for (i = 1; i < placed_tiles.size(); i++) {
        TileData tmp = placed_tiles[i];
        for (j = i; j >= 1 && tmp.coords.x < placed_tiles[j-1].coords.x; j--)
            placed_tiles[j] = placed_tiles[j-1];
        placed_tiles[j] = tmp;
    }
}

inline void Board::order_palced_tiles_by_y(){
    int i, j;
    for (i = 1; i < placed_tiles.size(); i++) {
        TileData tmp = placed_tiles[i];
        for (j = i; j >= 1 && tmp.coords.y < placed_tiles[j-1].coords.y; j--)
            placed_tiles[j] = placed_tiles[j-1];
        placed_tiles[j] = tmp;
    }
}

void Board::debug_print()
{
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            printf("%c ", game_board[x][y]);
        }
        printf("\n");
    }
    printf("----------------------------\n          ");
    for (int k = 0; k < 7; k++)
        printf("%c ", tile_dock[k]);
    printf("\n");
}
