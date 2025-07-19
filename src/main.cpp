#include "Map.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello SFML");
    window.setVerticalSyncEnabled(false);

    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/lostark_never_die.jpg")) {
        std::cerr << "Error in Loading Image" << std::endl;
    }
    sf::Sprite sprite(texture);
    
    // 폰트 설정
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Pretendard.ttf")) {
        std::cerr << "Error in Loading Font" << std::endl;
    }
    sf::Text text("LostArk Naver Pay", font, 50);

    sf::FloatRect textBounds = text.getLocalBounds();

    // 기준점을 텍스트 중심으로 설정
    text.setOrigin(
        textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);

    // 텍스르를 중앙에 배치
    text.setPosition(
        window.getSize().x / 2.f,
        window.getSize().y / 2.f);

    // 게임 루프 시작
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
    }
    return 0;
}
