//
//  board.cpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 10/31/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#include "board.hpp"
#include <stdio.h>

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

bool Board::update_board(sf::Vector2i board_pos, int rack_pos, char ch)
{
    if (rack_pos == -1) {
        if (game_board[board_pos.x][board_pos.y] != EMPTY)
            return false;
        game_board[board_pos.x][board_pos.y] = ch;
    } else {
        if (tile_dock[rack_pos] != EMPTY)
            return false;
        tile_dock[rack_pos] = ch;
    }
    
    printf("setting value to %c\n", ch);
    *last_char = EMPTY;
    
    debug_print();
    return true;
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
