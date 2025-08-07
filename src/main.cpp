#include "map/Block.hpp"
#include "map/Mapping.hpp"
#include "vehicle/Vehicle.hpp"

#include <iostream>

/*
    앞으로의 고려 사항

    1. 장애물을 도로에 매칭시키는 방법
    2. 자동차가 랜덤으로 나오는 방법
    3. 자동차와 플레이어 간의 충돌
    4. 플레이어의 점프 속도 / 자동차의 이동 속도 / 맵의 이동속도 동기화
    5. 자동차가 맵에 가려지게 하는 방법
    6. 이외 등등

*/

const sf::Vector2f WINDOW = {800, 800};
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW.x, WINDOW.y), "Crossy Road");
    window.setVerticalSyncEnabled(false);

    //MAP 
    Mapping map;
    Block block(window, map); 
    float diagOffset = block.getLen() * 5 / std::sqrt(2.0f);

    sf::Vector2f BASE(
        window.getSize().x / 2.f + diagOffset, 
        window.getSize().y / 2.f - block.getLen() * map.MAPLEN - diagOffset 
    );

    Vehicle vehicle = Vehicle(sf::Vector2f(706.f, 712.f), 3);
    sf::Clock clock;

    bool moveCheck = false;

    // 게임 루프 시작
    map.initMap();
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {

                switch (event.key.code) {

                    // 정확한 좌표를 알기 위한 코드(삭제 예정)
                    case sf::Keyboard::Up : {
                        vehicle.setPosition(vehicle.getPosition().x + 1.f, vehicle.getPosition().y - 1.f);
                        break;
                    }
                    case sf::Keyboard::Down : {
                        vehicle.setPosition(vehicle.getPosition().x - 1.f, vehicle.getPosition().y + 1.f);
                        break;                        
                    }
                    case sf::Keyboard::Left : {
                        vehicle.setPosition(vehicle.getPosition().x - 1.f, vehicle.getPosition().y - 1.f);
                        break;                        
                    }
                    case sf::Keyboard::Right : {
                        vehicle.setPosition(vehicle.getPosition().x + 1.f, vehicle.getPosition().y + 1.f);
                        break;                        
                    }
                    case sf::Keyboard::Enter : {
                        std::cout << vehicle.getPosition().x << ' ' << vehicle.getPosition().y;
                        break;
                    }
                    // 스페이스바 누를 시 이동 시작(수정 예정)
                    case sf::Keyboard::Space : {
                        moveCheck = true;
                        break;
                    }
                    // 정확한 좌표르 알기 위한 코드(삭제 예정)

                    case sf::Keyboard::S :
                        map.mapMove(1);
                        vehicle.moveWithMap(1);
                        break;
                    case sf::Keyboard::W :

                        // 좌표 계산 필요해서 잠시 주석 처리
                        // for (int i = 1; i <= 30; ++i) {
                        //     window.clear();

                        //     float LEN = block.getLen();
                        //     float LENDIA = block.getLenDiagonal();

                        //     float dx = LEN * (i / 30.0f);
                        //     float dy = LENDIA * (i / 30.0f);

                        //     map.mapping(window, block, {BASE.x - dx, BASE.y + dy});

                        //     window.display();
                        //     sf::sleep(sf::milliseconds(0.2)); 
                        // }
                        map.mapMove(2); 
                        vehicle.moveWithMap(2);
                        break;
                    case sf::Keyboard::A :
                        map.mapMove(3);
                        break;
                    case sf::Keyboard::D :
                        map.mapMove(4);
                        break;
                }
                
            }
        }
            

        window.clear();
        map.mapping(window, block, BASE);
        if (moveCheck) {
            vehicle.move(deltaTime);
        }
        window.draw(vehicle);
        window.display();
    }
    return 0;
}
