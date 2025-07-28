#include "character/Block.hpp"

Block::Block(int x, int y, int z, sf::Vector2f start) : top(sf::Triangles, 6), right(sf::Triangles, 6), left(sf::Triangles, 6), startingPosition(start),
    gridX(x), gridY(y), gridZ(z) {

    initSetting();
}   

void Block::initSetting() {

    // cube의 3D 논리 좌표를 2D 격자 좌표로 변경
    // 실제로는 300을 더하는 것이 아니라 공간을 잘라서 진행해야 함
    for (int i = 0; i < POINT_COUNT; i++) {
        points[i] = convertIsometric(gridX + cube[i].x, gridY + cube[i].y ,gridZ + cube[i].z) + startingPosition;
    }

    // top
    top[0].position = points[1];
    top[1].position = points[2];
    top[2].position = points[0];
    top[3].position = points[0];
    top[4].position = points[6];
    top[5].position = points[1];

    // left
    left[0].position = points[2];
    left[1].position = points[3];
    left[2].position = points[4];
    left[3].position = points[4];
    left[4].position = points[0];
    left[5].position = points[2];

    // right
    right[0].position = points[6];
    right[1].position = points[0];
    right[2].position = points[4];
    right[3].position = points[4];
    right[4].position = points[5];
    right[5].position = points[6];

    // lines

    lines.setPrimitiveType(sf::Lines);
    lines.resize(18);

    // 보이는 선분만 처리
    int edgePair[9][2] = {
        {0,2}, {0,4}, {0,6}, {1,2}, {1,6},
        {2,3}, {3,4}, {4,5}, {5,6}
    };

    int idx = 0;
    for (int i = 0; i < 9;i++) {
        int a = edgePair[i][0];
        int b = edgePair[i][1];

        lines[idx++] = sf::Vertex(points[a], sf::Color::Black);
        lines[idx++] = sf::Vertex(points[b], sf::Color::Black);
    }
}

/**
 *  @brief 등각투영을 통해 3차원 좌표를 2차원으로 변경해주는 함수
 */
sf::Vector2f Block::convertIsometric(int x, int y, int z) const {
    return {
        (x - y) * BLOCK_WIDTH / 2.0f,
        (x + y) * BLOCK_DEPTH / 2.0f - z * BLOCK_HEIGHT * 0.4f
    };
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(top, states);
    target.draw(left, states);
    target.draw(right, states);
    target.draw(lines, states);
}

// 만들어지는 전체 캐릭터의 중심점을 반환
// 다른 클래스로 옮기는 것도 좋은데, 아직 고민 중
sf::Vector2f Block::getCenter() {
    return  convertIsometric(gridX + cube[0].x, gridY + cube[0].y ,gridZ + cube[0].z) + startingPosition;
}