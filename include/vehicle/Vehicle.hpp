#pragma once

#include "VehicleBlock.hpp"
#include <vector>

class Vehicle : public sf::Drawable, public sf::Transformable { 
    private:
        std::vector<VehicleBlock> blockList;

        sf::Vector2f velocity;
        sf::Vector2f position;

        int blockCount;

        void initSetting();
    public:
        Vehicle(sf::Vector2f startPosition, int blockCount);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void move(float dt);
        void moveWithMap(int direction);

};