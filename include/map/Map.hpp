#pragma once

#include "Textture.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
class Map {
    private:
        
        
    public : 
        void draw(sf::RenderWindow& window, const sf::Vector2f& base);
        const int lenDigonal = 40;
        const float len = lenDigonal / sqrt(2);

};