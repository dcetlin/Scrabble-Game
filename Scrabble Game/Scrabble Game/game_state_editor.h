//
//  game_state_editor.hpp
//  Scrabble Game
//


#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "game_state.h"

const sf::Vector2i OFFSET(36, 40);
const float TILE_BOX_HEIGHT = 81.35;
const float TILE_BOX_WIDTH = 74.25;
const float TILE_HEIGHT = 80;
const float TILE_WIDTH = 72;
const float TILE_BOX_INDENT = 19;

class GameStateEditor : public GameState
{
private:
    
    sf::View gameView;
    sf::View guiView;
    sf::Text _mouse;
    
    sf::Sprite* is_being_dragged;
    sf::RectangleShape tile_outline;
    bool tile_outline_view;
    
    void getBoardTile(const sf::Vector2i&, sf::IntRect&);

    
public:
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
    GameStateEditor(Game* game);
};

#endif
