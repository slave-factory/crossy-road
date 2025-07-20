#include "map/Block.hpp"
#include "map/Mapping.hpp"

#include <iostream>

const sf::Vector2f WINDOW = {800, 800};
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW.x, WINDOW.y), "Crossy Road");
    window.setVerticalSyncEnabled(false);

    //MAP 
    Mapping map;
    Block block(window, map); 
   
    sf::Vector2f BASE(
    window.getSize().x / 2.f,                       // 화면 가로 중앙
    window.getSize().y / 2.f - block.getLen() * map.MAPLEN  // 화면 아래 중앙으로 약간 올림
    );

    // 게임 루프 시작
    map.initMap();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {

                switch (event.key.code) {
                    case sf::Keyboard::S :
                        map.mapMove(1);
                        break;
                    case sf::Keyboard::W :
                        for (int i = 1; i <= 30; ++i) {
                        window.clear();

                        float LEN = block.getLen();
                        float LENDIA = block.getLenDiagonal();

                        float dx = LEN * (i / 30.0f);
                        float dy = LENDIA * (i / 30.0f);

                        map.mapping(window, block, {BASE.x - dx, BASE.y + dy});

                        window.display();
                        sf::sleep(sf::milliseconds(0.2)); 
                        }
                        map.mapMove(2); 


                        break;
                    case sf::Keyboard::A :
                        map.mapMove(4);
                        break;
                    case sf::Keyboard::D :
                        map.mapMove(3);
                        break;
                }
                
            }
        }
            

        window.clear();
        map.mapping(window, block, BASE);
        window.display();
    }
    return 0;
}
