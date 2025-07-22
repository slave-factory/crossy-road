#include "character/Canvas.hpp"

Canvas::Canvas() {

}

void Canvas::createRenderTexture(sf::Sprite& sprite, sf::Vector2f start) {

    int ch[3][3][3] = {
        {
            {0,0,0},
            {0,1,0},
            {0,0,0}
        },
        {
            {0,1,0},
            {1,1,1},
            {0,1,0}
        },
        {
            {0,0,0},
            {0,1,0},
            {0,0,0}
        }
    };

    renderTexture.create(MAX_SIZE, MAX_SIZE);

    for (int z = 0; z < 3; z++) {
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (ch[z][y][x]) {
                    Block temp = Block(x,y,z, start);
                    renderTexture.draw(temp);
                }
            }
        }
    }

    renderTexture.display();
    sprite.setTexture(renderTexture.getTexture());
}
