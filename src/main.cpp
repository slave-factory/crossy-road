// 이거 상당히 어려운데요

#include "character/Character.hpp"

/*
    1. 중심점 계산 공식
    2. 캐릭터 생성
    3. 운동 공식 적용


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
                }
            }
        }
        else {  // 점프 중일 때는 점프만
            character.move(deltaTime);
            if (character.checkCurrentJumpTime(deltaTime)) {
                character.setIsJumping(false);
            }
        }


        window.clear();
        window.draw(character);
        window.display();

    }
}