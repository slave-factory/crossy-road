#include "vehicle/VehicleBlock.hpp"

VehicleBlock::VehicleBlock(sf::Vector2f startPosition) : position(startPosition) {
    initSetting();
}

void VehicleBlock::initSetting() {
    sf::Vector2f points[7] = {
        {position.x, position.y}, // 0: 기준점 (하단 중심)
        {position.x, position.y - 2 * len}, // 1: 꼭대기
        {position.x + len, position.y - len}, // 2: 오른쪽 위
        {position.x + len, position.y - len + lenDiagonal}, // 3
        {position.x, position.y + lenDiagonal}, // 4: 앞 하단
        {position.x - len, position.y - len + lenDiagonal}, // 5
        {position.x - len, position.y - len} // 6: 왼쪽 위
    };


        // 윗면
        top.setPointCount(4);
        top.setPoint(0, points[0]); // 꼭대기
        top.setPoint(1, points[2]);
        top.setPoint(2, points[1]);
        top.setPoint(3, points[6]);
        top.setFillColor(sf::Color(100, 100, 100));  // 밝은 검정

        // 오른쪽 면
        right.setPointCount(4);
        right.setPoint(0, points[0]);
        right.setPoint(1, points[2]);
        right.setPoint(2, points[3]);
        right.setPoint(3, points[4]);
        right.setFillColor(sf::Color(60, 60, 60));  // 중간 검정

        // 왼쪽 면
        left.setPointCount(4);
        left.setPoint(0, points[0]);
        left.setPoint(1, points[4]);
        left.setPoint(2, points[5]);
        left.setPoint(3, points[6]);
        left.setFillColor(sf::Color(20, 20, 20));  // 어두운 검정

        // 경계
        outLine.setPointCount(6);
        outLine.setPoint(0,points[1]);
        outLine.setPoint(1,points[2]);
        outLine.setPoint(2,points[3]);
        outLine.setPoint(3,points[4]);
        outLine.setPoint(4,points[5]);
        outLine.setPoint(5,points[6]);

        hitBox = outLine.getGlobalBounds();

        bounds.setPosition(sf::Vector2f(hitBox.left + 10.f, hitBox.top + 10.f));
        bounds.setSize(sf::Vector2f(hitBox.width - 20.f, hitBox.height - 20.f));
        bounds.setOutlineThickness(1.f);
        bounds.setOutlineColor(sf::Color::Red);
        bounds.setFillColor(sf::Color::Transparent);
}

void VehicleBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(top, states);
    target.draw(left,states);
    target.draw(right, states);
    target.draw(bounds, states);
}