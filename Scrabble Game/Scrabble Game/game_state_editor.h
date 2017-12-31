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
#include "tile_manager.hpp"

const sf::Vector2i OFFSET(36, 40);

class GameStateEditor : public GameState
{
private:
    
    sf::View gameView;
    sf::View guiView;
    sf::Text _mouse;
    
    TileDisplay::Tile* is_being_dragged;
    sf::Vector2i last_position;
    sf::RectangleShape tile_outline;
    bool tile_outline_view;
    bool button_isclicked;
    bool isFirstMove;
    
    Board game_board;
    TileManager* tile_manager;
    
    void getBoardTile(const sf::Vector2i&, sf::IntRect&);
    
public:
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
    GameStateEditor(Game* game);
    ~GameStateEditor();
};

#endif
