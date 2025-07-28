#include "character/Character.hpp"

/*
    고민 중인 내용

    1. 캐릭터 사이즈 축소
    2. 충돌 범위 설정 => 바로 window에 그린 그림이므로 히트 박스 설정이 필요하다
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
                if(event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Left) {
                        character.changeDirection(false);
                    }
                    else if (event.key.code == sf::Keyboard::Right) {
                        character.changeDirection(true);
                    }
                }

                // 캐릭터 변경을 확인하기 위한 임시 기능
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    character.changeCharacter("chicken");
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    character.changeCharacter("cross");
                }
                // 캐릭터 변경을 확인하기 위한 임시 기능

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