// 지금은 내부에서 3차원 배열을 만들지만 이후에는 JSON 혹은 TXT에서 받아오는 방식으로 리펙토링하기

#pragma once

#include "Block.hpp"

// 블록의 사이즈 기준으로 캐릭터 생성
class Canvas {

    private:
        sf::RenderTexture renderTexture;
        
        // 캐릭터는 20 * 20 * 20(논리 좌표 기준) 사이즈로 임의로 설정
        const float MAX_SIZE = 20.f * Block::BLOCK_WIDTH;
    public:
        Canvas();
        void createRenderTexture(sf::Sprite& sprite, sf::Vector2f start);


};