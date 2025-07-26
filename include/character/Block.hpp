#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

// 실제 좌표가 아닌 격자 좌표를 기준으로 만들기

class Block : public sf::Drawable, public sf::Transformable{

    private:

        void initSetting();

        sf::VertexArray top, left, right, lines;
        sf::Vector2f convertIsometric(int x, int y, int z) const;
        
        // 격자 좌표
        int gridX, gridY, gridZ;

        // 블럭 하나의 크기

        const int POINT_COUNT = 8;
        
        // 3차원 기준 논리 좌표
        // 순서는 플젝 내부에서의 정육면체 점 순서를 따름
        sf::Vector3f cube[8] = {
            {1,1,1}, {0,0,1}, {0,1,1}, {0,1,0},
            {1,1,0}, {1,0,0}, {1,0,1}, {0,0,0}
        };
        
        // 실제 화면 속에서의 좌표
        sf::Vector2f points[8];
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2f startingPosition;
    public:

        // 논리 좌표 x, y, z를 기준으로 블럭 생성
        Block(int x, int y, int z, sf::Vector2f start);
        static constexpr float BLOCK_WIDTH = 12.f, BLOCK_DEPTH = 12.f, BLOCK_HEIGHT = 20.f;
    
        // 3D 도형의 중심점을 얻기 위한 함수
        sf::Vector2f getCenter();
};