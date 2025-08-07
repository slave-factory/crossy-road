#include "vehicle/Vehicle.hpp"

Vehicle::Vehicle(sf::Vector2f startPosition, int blockCount) 
    : position(startPosition), blockCount(blockCount), velocity(sf::Vector2f(-50.f, -50.f)) {
    initSetting();
}

/**
 *  @brief 장애물의 기본적인 세팅
 *  @details 블럭 연결 및 vector에 저장
 */
void Vehicle::initSetting() {
    for (int i = 0; i < blockCount; i++) {
        VehicleBlock vehicleBlock = VehicleBlock(position + sf::Vector2f(30.f, 30.f) * static_cast<float>(i));
        blockList.push_back(vehicleBlock);
    }
    setOrigin(position);
    setPosition(position);
}

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (int i = 0; i < blockCount; i++) {
        target.draw(blockList[i], states);
    }
}

void Vehicle::move(float dt) {
    setPosition(getPosition().x + velocity.x * dt, getPosition().y + velocity.y * dt);
}

void Vehicle::moveWithMap(int direction) {
    switch (direction)
    {
        case 1:{
            setPosition(getPosition().x + 30.f, getPosition().y - 30.f);
            break;
        }
        case 2:{
            setPosition(getPosition().x - 30.f, getPosition().y + 30.f);
            break;
        }
        case 3:{
            break;
        }
        case 4:{
            break;
        }
    }
}