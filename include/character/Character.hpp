#pragma once

#include "CharacterBlock.hpp"
#include "Direction.hpp"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class Character : public sf::Drawable, public sf::Transformable{

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Vector2f startingPoint;

        void initSetting();

        bool isJumping;
        Direction currentDirection;

        const int CHARACTER_WIDTH = 9, CHARACTER_HEIGHT = 9, CHARACTER_DEPTH = 13;

        // 실제 캐릭터를 회전시키는 함수
        void rotateCharacter(bool isRight);

        sf::Vector2f velocity;
        sf::Vector2f gravity;

        const float JUMP_TIME = 0.2;
        float currentJumpTime;

        void loadFromJson(const std::string& characterName);

        // 히트 박스 관리 부분
        sf::CircleShape hit;
        sf::FloatRect hitBox;
        sf::RectangleShape bounds;

        // z가 클수록 윗층에 배치
        int design[20][13][13];

    public:
        Character(sf::Vector2f start);
        void move(float dt);

        void changeDirection(bool isRight);

        bool checkCurrentJumpTime(float dt);

        // 점프 중에는, 다른 입력을 무시할 수 있도록 하기
        void setIsJumping(bool isJumping) {
            this->isJumping = isJumping;   
        }
        bool getIsJumping() {
            return isJumping;
        }

        /**
         *  @brief 속도를 설정할 수 있는 함수
         *  @details 이동 방향에 따른 시작 속도 차이를 해소하기 위한 함수
         */
        void setVelocity(sf::Vector2f velocity) {
            this->velocity = velocity;
        }
    
        Direction getCurrentDirection() {
            return currentDirection;
        }

        void changeCharacter(const std::string& characterName);
};