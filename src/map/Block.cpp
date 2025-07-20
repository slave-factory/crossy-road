#include "SFML/Graphics.hpp"
#include <iostream>
#include "map/Mapping.hpp"
#include "map/Block.hpp"  


Block::Block(sf::RenderWindow& window, Mapping& map)
    : len(static_cast<float>(window.getSize().x) / Mapping::MAPLEN * 0.75),
      lenDiagonal(len / std::sqrt(2.0f)) {
  
}

void Block::draw(sf::RenderWindow& window, const sf::Vector2f& base) {
    
    sf::Vector2f points[7] = {
        {base.x, base.y}, // 0
        {base.x, base.y - 2*len}, // 1
        {base.x + len, base.y - len}, // 2
        {base.x + len, base.y - len + lenDiagonal}, // 3
        {base.x, base.y + lenDiagonal}, // 4
        {base.x - len, base.y - len + lenDiagonal}, // 5
        {base.x - len, base.y - len} // 6
    };

    sf::Vertex lines[] = {
    
    sf::Vertex(points[0]), sf::Vertex(points[2]),
    sf::Vertex(points[0]), sf::Vertex(points[4]),
    sf::Vertex(points[0]), sf::Vertex(points[6]),

    sf::Vertex(points[1]), sf::Vertex(points[2]),
    sf::Vertex(points[2]), sf::Vertex(points[3]),
    sf::Vertex(points[3]), sf::Vertex(points[4]),
    sf::Vertex(points[4]), sf::Vertex(points[5]),
    sf::Vertex(points[5]), sf::Vertex(points[6]),
    sf::Vertex(points[6]), sf::Vertex(points[1])

    };

    
    window.draw(lines, sizeof(lines) / sizeof(sf::Vertex), sf::Lines);

}