//
//  tiles.hpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 9/2/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#ifndef TILE_DISPLAY_H
#define TILE_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>

class TileDisplay {
    
    const char SPACE = '_';
    
public:
    struct Tile {
        char ch;
        sf::Sprite* sprite;
        
        Tile(char c, sf::Sprite*s) : ch(c), sprite(s) {};
    };
    
    TileDisplay(sf::Texture t) : tileTexture(t){};
    ~TileDisplay();
    void newTile(char c, int x, int y);
    void display_tiles(sf::RenderWindow&);
    void move_to_last(sf::Sprite*);
    std::vector<Tile*> visible_tiles;
    
    
private:
    sf::Texture tileTexture;
    void getRect(char c, sf::IntRect&);
};

#endif
