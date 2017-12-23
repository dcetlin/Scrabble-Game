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
}

void Board::getBoardTile(const sf::Vector2i& mouse_position, sf::IntRect& rect, sf::Vector2<int>& board_pos, int& rack_pos, int& x_pos, int& y_pos)
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
            printf("rack_pos: %d\n, grid: (%d, %d)\n", rack_pos, x_pos, y_pos);
            return;
        }
        else
            y = 14 * TILE_BOX_HEIGHT + TILE_BOX_INDENT;
    }
    
    rect.left = (int) ((x - TILE_BOX_INDENT) / TILE_BOX_WIDTH) * TILE_BOX_WIDTH + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_HEIGHT) / 2;
    rect.top = (int)((y - TILE_BOX_INDENT) / TILE_BOX_HEIGHT) * TILE_BOX_HEIGHT + TILE_BOX_INDENT + (TILE_BOX_WIDTH - TILE_WIDTH) / 2;
    rect.height = (int) TILE_BOX_HEIGHT;
    rect.width = (int) TILE_BOX_WIDTH;
    
    x_pos = (rect.left) / TILE_BOX_WIDTH;
    y_pos = (rect.top - TILE_BOX_INDENT) / TILE_BOX_HEIGHT;
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

Board::Multi Board::getMultiplier(int x, int y)
{
    if (((x == 0 || x == 14) and (y == 0 || y == 7 || y == 14))
        or ((x == 7) and (y == 0 || y == 14)))
        return Board::Multi::TRIP_WORD;
    else if ((((x == y) || (x == 14 - y)) and ((x >= 1 && x <= 4) || (x == 7) || (x >= 10 && x <= 14))))
        return Board::Multi::DOUB_WORD;
    else if (((x == 1 || x == 14) and (y == 5 || y == 9))
             or ((x == 5 || x == 9) and (y == 1 || y == 5 || y == 9 || y == 14)))
        return Board::Multi::TRIP_LET;
    else if (((x == 0 || y == 0 || x == 14 || y == 14) && (x == 3 || x == 11 || y == 3 || y == 11))
             or ((x == 2 || y == 2 || x == 12 || y == 12) && (x == 6 || x == 6 || y == 8 || y == 8))
             or ((x == 3 || y == 3 || x == 11 || y == 11) && (x == 7 || y == 7))
             or ((x == y) && (x == 6 || x == 8)))
        return Board::Multi::TRIP_WORD;
    else
        return Board::Multi::NONE;
}



