#pragma once
#include <SFML/Graphics.hpp>

class Map : public sf::Drawable, public sf::Transformable {
    
    private : 
        void draw(sf::RenderTaget& target) const;
    

}