//
//  button.cpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 12/25/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#include "button.hpp"

Button::Button(sf::Sprite* my_normal,sf::Sprite* my_clicked,sf::Vector2f location)
{
    normal = my_normal;
    clicked = my_clicked;
    currentSpr = normal;
    isClicked = false;
    
    normal->setPosition(location);
    clicked->setPosition(location);
    
}

bool Button::checkInitialClick (sf::Vector2i mouse_position)
{
    if (currentSpr->getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
        setState(true);
        return true;
    }
    return false;
}

bool Button::checkReleaseClick(sf::Vector2i mouse_position)
{
    if (isClicked) {
        setState(false);
        return currentSpr->getGlobalBounds().contains(mouse_position.x, mouse_position.y);
    }
    return false;
}

void Button::setState(bool which) {
    isClicked = which;
    if (isClicked)
        currentSpr = clicked;
    else
        currentSpr = normal;
}

void Button::draw_button(sf::RenderWindow& window)
{
    window.draw(*currentSpr);
}
