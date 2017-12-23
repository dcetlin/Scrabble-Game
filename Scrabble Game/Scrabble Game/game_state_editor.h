//
//  game_state_editor.hpp
//  Scrabble Game
//


#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "pixel_data.h"
#include "board.hpp"
#include "tile_display.h"

const sf::Vector2i OFFSET(36, 40);

class GameStateEditor : public GameState
{
private:
    
    sf::View gameView;
    sf::View guiView;
    sf::Text _mouse;
    
    sf::Sprite* is_being_dragged;
    sf::RectangleShape tile_outline;
    bool tile_outline_view;
    
    Board game_board;
    
    void getBoardTile(const sf::Vector2i&, sf::IntRect&);
    
public:
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
    GameStateEditor(Game* game);
};

#endif
