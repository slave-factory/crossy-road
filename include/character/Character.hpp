#pragma once

#include "Canvas.hpp"
#include "Direction.hpp"

class Character : public sf::Drawable, public sf::Transformable{

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite sprite;

        Canvas renderCanvas;

        sf::Vector2f startingPoint;

        void initSetting();

        bool isJumping;
        Direction currentDirection;
    public:
        Character(sf::Vector2f start);
        void move();

        bool getIsJumping() {return isJumping;}
};