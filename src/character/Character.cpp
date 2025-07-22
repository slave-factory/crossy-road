#include "character/Character.hpp"

/*
    추가 고려 내용
    
    1. 캐릭터는 리스트에 넣어서 관리
    2. 특정 캐릭터를 골라서 그리는 방법
    3. 여러 캐릭터들 렌더링 하는 방법

*/

Character::Character(sf::Vector2f start) : renderCanvas(Canvas()), startingPoint(start), isJumping(false), currentDirection(Direction::FRONT) {
    initSetting();
}

void Character::initSetting() {
    setOrigin(startingPoint);
    setPosition(startingPoint);
    renderCanvas.createRenderTexture(sprite, startingPoint);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
}

void Character::move() {

    switch (currentDirection) {
        case Direction::FRONT : {
            setPosition(getPosition().x + 10.f, getPosition().y - 10.f);
            break;
        }
        case Direction::BACK : {
            setPosition(getPosition().x - 10.f, getPosition().y + 10.f);
            break;
        }
        case Direction::LEFT : {
            setPosition(getPosition().x - 10.f, getPosition().y - 10.f);
            break;
        }
        case Direction::RIGHT : {
            setPosition(getPosition().x + 10.f, getPosition().y + 10.f);
            break;
        }
    }

}