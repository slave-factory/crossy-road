#pragma once

#include <SFML/Graphics.hpp>

class Block; 

class Mapping {
    public:
        static const int MAPLEN  = 20;
        static const int MAX_Z = 5;
        int mapTile[5][MAPLEN][MAPLEN];
        void mapping(sf::RenderWindow& window, Block& Block, const sf::Vector2f& base);
        void mapMove(int dir);
        void initMap();
};