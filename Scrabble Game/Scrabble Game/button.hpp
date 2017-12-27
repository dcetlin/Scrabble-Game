//
//  button.hpp
//  Scrabble Game
//
//  Created by Daniel Cetlin on 12/25/17.
//  Copyright © 2017 Daniel Cetlin. All rights reserved.
//

#ifndef button_hpp
#define button_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Button {
public:
    Button (sf::Sprite* my_normal,sf::Sprite* my_clicked,sf::Vector2f location);
    bool checkInitialClick (sf::Vector2i);
    bool checkReleaseClick (sf::Vector2i);
    void draw_button(sf::RenderWindow&);
    void setState(bool);
private:
    sf::Sprite* normal;
    sf::Sprite* clicked;
    sf::Sprite* currentSpr;
    bool isClicked;
};

#endif /* button_hpp */
