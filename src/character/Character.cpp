#include "character/Character.hpp"


Character::Character(sf::Vector2f start) : startingPoint(start), isJumping(false), currentDirection(Direction::FRONT)
    , gravity(0, 4900.f), velocity(250.f,-740.f), currentJumpTime(0) {
    initSetting();
}

void Character::initSetting() {

    // 중심점 계산용...캐릭터 최대 크기를 기반으로 중심점 생성
    Block temp = Block(CHARACTER_WIDTH / 2, CHARACTER_HEIGHT / 2, CHARACTER_DEPTH / 2, startingPoint);

    sf::Vector2f center = temp.getCenter();
    setOrigin(center);
    setPosition(center);
}


/**
 *  @brief 캐릭터를 화면에 그리는 함수
 *  @details design 3차원 배열을 읽어서 window에 직접 그림
 * 
 * 
 */
void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    
    for (int z = 0; z < CHARACTER_DEPTH; z++) {
        for (int y = 0; y < CHARACTER_HEIGHT; y++) {
            for (int x = 0; x < CHARACTER_WIDTH; x++) {
                if (design[z][y][x]) {
                    Block block = Block(x,y,z,startingPoint);
                    target.draw(block, states);
                }
            }
        }
    }
}


/** 
*   @brief 포물선 운동 기반 점프 및 이동
*
    @details
    움직임의 작동 원리 : n초 동안 d만큼 이동한다 X -> d만큼 이동하기 위해 n초를 사용한다
    움직이는 시간의 최대치를 정해두고 그 시간 안에 점프를 마무리하는 방식으로 로직을 구현했기에
    이동거리보다는 이동시간에 더욱 중점을 둔 이동 방식
    ==> 솔직히 더 좋은 방법이 있을 거 같은데, 아직 아이디어가 없음

    @todo
    이동 방향에 따라 x,y 방향의 시작 속도가 달라질 수 있기 때문에 이를 수정할 필요 있음

    @param dt
*/
void Character::move(float dt) {

    switch (currentDirection) {
        case Direction::FRONT : {
            setPosition(getPosition().x + velocity.x * dt, getPosition().y + (velocity.y * dt + 0.5f * gravity.y * dt * dt));
            velocity.y += gravity.y * dt;
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

/**
 *  @brief 캐릭터를 회전시키는 함수
 *  @details rotated 배열에 design을 회전시켜서 저장한 후 다시 받아옴
 * 
 *  @todo design 3차원 배열은 이후 JSON에서 받아오는 내용으로 개선 가능
 * 
 */
void Character::rotateCharacter(bool isRight) {
    int rotated[CHARACTER_DEPTH][CHARACTER_HEIGHT][CHARACTER_WIDTH];

    // 회전하기
    if (isRight) {
        for (int z = 0; z < CHARACTER_DEPTH; z++) {
            for (int y = 0; y < CHARACTER_HEIGHT; y++) {
                for (int x = 0; x < CHARACTER_WIDTH; x++) {
                    rotated[z][x][CHARACTER_WIDTH - 1 - y] = design[z][y][x];
                }
            }
        }
    }
    else {
        for (int z = 0; z < CHARACTER_DEPTH; z++) {
            for (int y = 0; y < CHARACTER_HEIGHT; y++) {
                for (int x = 0; x < CHARACTER_WIDTH; x++) {
                    rotated[z][CHARACTER_HEIGHT - 1 - x][y] = design[z][y][x];
                }
            }
        }
    }

    for (int z = 0; z < CHARACTER_DEPTH; z++) {
        for (int y = 0; y < CHARACTER_HEIGHT; y++) {
            for (int x = 0; x < CHARACTER_WIDTH; x++) {
                design[z][y][x] = rotated[z][y][x];
            }
        }
    }
}

// enum 클래스의 순서를 기반으로 방향 변경
void Character::changeDirection(bool isRight) {

    int curr = static_cast<int>(currentDirection);
    int directionCount = 4;

    if (isRight) {
        curr = (curr + 1) % 4;
    }
    else {
        curr = (curr - 1 + directionCount) % 4;
    }

    rotateCharacter(isRight);

    currentDirection = static_cast<Direction>(curr);
}

/**
 *  @brief 점프 시간 확인 여부
 *  @details 점프 할 수 있는 시간을 판단하여 이동의 지속 여부 판단
 *  
 *  @return 점프 진행 중일 경우 false, 점프가 끝났을 경우 true
 * 
 */
bool Character::checkCurrentJumpTime(float dt) {

    currentJumpTime += dt;;

    if (currentJumpTime >= JUMP_TIME) {
        currentJumpTime = 0;
        velocity.y = -740.f;    // 수정 필요 -> move 함수 부분 확인
        return true;
    }
    else {
        return false;
    }

}