#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Mapping;

class Block {
private:
    const float len;
    const float lenDiagonal;

public:
    Block(sf::RenderWindow& window, Mapping& map); // 생성자 선언

    void draw(sf::RenderWindow& window, const sf::Vector2f& base);
    float getLenDiagonal() const { return lenDiagonal; }
    float getLen() const { return len; }
    
};
