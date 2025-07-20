#include "map/Map.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Hello SFML");
    window.setVerticalSyncEnabled(false);

    //MAP 
    Map block;
    sf::Vector2f BASE = {400, 400};
    // 게임 루프 시작
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        block.draw(window,BASE);
        block.draw(window,{BASE.x + block.len, BASE.y + block.len});
        block.draw(window,{BASE.x + block.len, BASE.y - block.len});
        block.draw(window,{BASE.x + block.len - block.len, BASE.y - block.len - block.len});
        window.display();
    }
    return 0;
}
