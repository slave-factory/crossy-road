#pragma once

#include <SFML/Graphics.hpp>

class Block; 

class Mapping {
    public:
        static const int MAPLEN  = 20;
        static const int MAX_Z = 5;
        static const int mapFreespace = 5;
        const int moveTime = 30;
        int ghostZ = 1, ghostY = 13, ghostX = 6;
        int mapTile[MAX_Z][MAPLEN + 2*mapFreespace][MAPLEN + 2*mapFreespace]; // [Z][Y][X]
        void mapping(sf::RenderWindow& window, Block& Block, const sf::Vector2f& base);
        void mapMove(int dir);
        void initMap();
        void placeGhostBlock();
};