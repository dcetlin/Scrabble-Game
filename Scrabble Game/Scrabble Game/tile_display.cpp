//
//  tiles.cpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 9/2/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//left, top, width, height

#include "tile_display.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <stdio.h>

void TileDisplay::getRect(char c, sf::IntRect& rect)
{
    if (c == SPACE)
        c = '{';
    
    int row = (c - 'a') / 8;
    int col = (c - 'a') % 8;
    
    rect.left = round(col * 297.25);
    rect.top = round(row * 328.25);
    rect.width = round(297.25);
    rect.height = round(328.25);
}

void TileDisplay::newTile(char c, int x, int y)
{
    sf::IntRect rect;
    getRect(c, rect);
    sf::Sprite* s = new sf::Sprite(tileTexture, rect);
    s->setPosition(x, y);
    s->scale(.2422, .2437);
    
    Tile* t = new Tile(c, s);
    visible_tiles.push_back(t);
}

void TileDisplay::display_tiles(sf::RenderWindow& window)
{
    for (Tile* tile: visible_tiles) {
        sf::Sprite* s = tile->sprite;
        if (s != nullptr)
            window.draw(*s);
    }
    
}

TileDisplay::~TileDisplay()
{
    for (std::vector<Tile*>::iterator it = visible_tiles.begin(); it != visible_tiles.end() - 1; it++) {
        if (*it != nullptr) {
            if ((*it)->sprite != nullptr) {
                delete (*it)->sprite;
            }
            delete (*it);
        }
    }
}

void TileDisplay::move_to_last(sf::Sprite* s)
{
    size_t curr = 0;
    for (curr = 0; curr < visible_tiles.size(); curr++) {
        if (visible_tiles[curr]->sprite == s)
            break;
    }
    std::iter_swap(visible_tiles.end() - 1, visible_tiles.begin() + curr);
}


