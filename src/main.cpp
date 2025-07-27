#include "character/Character.hpp"

/*
    나중에 할 때는 Character 내부에 있는 
    design 배열에 std::swap 사용해서 json 내용과 바꾸기
*/

int main() {

    sf::RenderWindow window;
    sf::Vector2f screenSize(1200.f, 1200.f);

    sf::Event event;

    Character character= Character(sf::Vector2f(300.f, 300.f));

    window.create(sf::VideoMode(screenSize.x, screenSize.y), "Player");

    sf::Clock clock;

    while (window.isOpen()) {

        float deltaTime = clock.restart().asSeconds();


        if (!character.getIsJumping()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // 이동 및 회전 이벤트
                if(event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Left) {
                        character.changeDirection(false);
                    }
                    else if (event.key.code == sf::Keyboard::Right) {
                        character.changeDirection(true);
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    character.setIsJumping(true);
                    
                    // 현재 방향에 따라서 x,y축 방향으로의 시작 속도 설정
                    switch (character.getCurrentDirection())
                    {
                        case Direction::FRONT : {
                            character.setVelocity(sf::Vector2f(250.f, -740.f));
                            break;
                        }
                        case Direction::BACK : {
                            character.setVelocity(sf::Vector2f(-250.f, -240.f));
                            break;
                        }
                        case Direction::LEFT : {
                            character.setVelocity(sf::Vector2f(-250.f, -740.f));
                            break;
                        }
                        case Direction::RIGHT : {
                            character.setVelocity(sf::Vector2f(250.f, -240.f));
                            break;
                        }
                    }
                }
            }
        }
        else {  // 점프 중일 때는 점프만 ==> 점프 딜레이 고려하기
            if (character.checkCurrentJumpTime(deltaTime)) {
                character.setIsJumping(false);
                continue;
            }
            character.move(deltaTime);
        }


        window.clear();
        window.draw(character);
        window.display();

    }
}