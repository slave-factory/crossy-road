#include "SFML/Graphics.hpp"
#include <iostream>
#include "map/Mapping.hpp"
#include "map/Block.hpp"  


Block::Block(sf::RenderWindow& window, Mapping& map)
    : len(static_cast<float>(window.getSize().x) / Mapping::MAPLEN * 0.75),
      lenDiagonal(len / std::sqrt(2.0f)) {
  
}
void Block::draw(sf::RenderWindow& window, const sf::Vector2f& base, int color) {
    // 7개 꼭짓점 계산
    sf::Vector2f points[7] = {
        {base.x, base.y}, // 0: 기준점 (하단 중심)
        {base.x, base.y - 2 * len}, // 1: 꼭대기
        {base.x + len, base.y - len}, // 2: 오른쪽 위
        {base.x + len, base.y - len + lenDiagonal}, // 3
        {base.x, base.y + lenDiagonal}, // 4: 앞 하단
        {base.x - len, base.y - len + lenDiagonal}, // 5
        {base.x - len, base.y - len} // 6: 왼쪽 위
    };
    if (color == 1) {
        // 윗면
        sf::ConvexShape top;
        top.setPointCount(4);
        top.setPoint(0, points[0]); // 꼭대기
        top.setPoint(1, points[2]);
        top.setPoint(2, points[1]);
        top.setPoint(3, points[6]);
        top.setFillColor(sf::Color(200, 200, 200));  // 밝은 회색
        window.draw(top);

        // 오른쪽 면
        sf::ConvexShape right;
        right.setPointCount(4);
        right.setPoint(0, points[0]);
        right.setPoint(1, points[2]);
        right.setPoint(2, points[3]);
        right.setPoint(3, points[4]);
        right.setFillColor(sf::Color(160, 160, 160));  // 중간 회색
        window.draw(right);

        // 왼쪽 면
        sf::ConvexShape left;
        left.setPointCount(4);
        left.setPoint(0, points[0]);
        left.setPoint(1, points[4]);
        left.setPoint(2, points[5]);
        left.setPoint(3, points[6]);
        left.setFillColor(sf::Color(120, 120, 120));  // 어두운 회색
        window.draw(left);

        // ⚪ 선분
        sf::Vertex lines[] = {
            sf::Vertex(points[0]), sf::Vertex(points[2]),
            sf::Vertex(points[0]), sf::Vertex(points[4]),
            sf::Vertex(points[0]), sf::Vertex(points[6]),

            sf::Vertex(points[1]), sf::Vertex(points[2]),
            sf::Vertex(points[2]), sf::Vertex(points[3]),
            sf::Vertex(points[3]), sf::Vertex(points[4]),
            sf::Vertex(points[4]), sf::Vertex(points[5]),
            sf::Vertex(points[5]), sf::Vertex(points[6]),
            sf::Vertex(points[6]), sf::Vertex(points[1])
        };

        window.draw(lines, sizeof(lines) / sizeof(sf::Vertex), sf::Lines);
    }
    
    if (color == 2) {
        // 윗면
        sf::ConvexShape top;
        top.setPointCount(4);
        top.setPoint(0, points[0]); // 꼭대기
        top.setPoint(1, points[2]);
        top.setPoint(2, points[1]);
        top.setPoint(3, points[6]);
        top.setFillColor(sf::Color(200, 100, 100));  // 밝은 회색
        window.draw(top);

        // 오른쪽 면
        sf::ConvexShape right;
        right.setPointCount(4);
        right.setPoint(0, points[0]);
        right.setPoint(1, points[2]);
        right.setPoint(2, points[3]);
        right.setPoint(3, points[4]);
        right.setFillColor(sf::Color(160, 60, 60));  // 중간 회색
        window.draw(right);

        // 왼쪽 면
        sf::ConvexShape left;
        left.setPointCount(4);
        left.setPoint(0, points[0]);
        left.setPoint(1, points[4]);
        left.setPoint(2, points[5]);
        left.setPoint(3, points[6]);
        left.setFillColor(sf::Color(120, 0, 0));  // 어두운 회색
        window.draw(left);

        // ⚪ 선분
        sf::Vertex lines[] = {
            sf::Vertex(points[0]), sf::Vertex(points[2]),
            sf::Vertex(points[0]), sf::Vertex(points[4]),
            sf::Vertex(points[0]), sf::Vertex(points[6]),

            sf::Vertex(points[1]), sf::Vertex(points[2]),
            sf::Vertex(points[2]), sf::Vertex(points[3]),
            sf::Vertex(points[3]), sf::Vertex(points[4]),
            sf::Vertex(points[4]), sf::Vertex(points[5]),
            sf::Vertex(points[5]), sf::Vertex(points[6]),
            sf::Vertex(points[6]), sf::Vertex(points[1])
        };

        window.draw(lines, sizeof(lines) / sizeof(sf::Vertex), sf::Lines);
    }

    
}
