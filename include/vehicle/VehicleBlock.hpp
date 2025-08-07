#pragma once

#include <SFML/Graphics.hpp>

class VehicleBlock : public sf::Drawable, sf::Transformable {

    private:
        sf::ConvexShape top, left, right;
        sf::ConvexShape outLine;
        sf::FloatRect hitBox;
        sf::RectangleShape bounds;

        sf::Vector2f position;

        float len = 30.f;
        float lenDiagonal = 21.2132f;
        void initSetting();
    public:
        VehicleBlock(sf::Vector2f startPosition);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};