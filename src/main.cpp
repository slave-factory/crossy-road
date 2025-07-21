#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"

enum class CollisionType {
    Idle,
    Obstacle,
    Vehicle,
    Drowned,
    CoinCollected
};

bool isColliding(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.intersects(b);
}

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Collision System");
    // window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    // 플레이어
    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setPosition(100, 100);
    player.setFillColor(sf::Color::Green);
    float speed = 50.f;

    // 자동차
    sf::RectangleShape car(sf::Vector2f(100, 50));
    car.setPosition(200, 100);

    // 코인
    sf::CircleShape coin(25.f);
    coin.setFillColor(sf::Color::Yellow);
    coin.setPosition(150.f, 200.f);
    
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Pretendard.ttf")) {
        std::cerr << "폰트 파일을 불러올 수 없습니다.\n";
        return -1;
    }
    // sf::Text text;
    sf::Text text("C", font, 40);
    /* text.setString("C");
    text.setCharacterSize(40); */
    text.setFillColor(sf::Color::Black);
    
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);

    sf::Vector2f circleCenter = coin.getPosition() + sf::Vector2f(coin.getRadius(), coin.getRadius());
    text.setPosition(circleCenter);

    // (임시) 물
    sf::RectangleShape water(sf::Vector2f(700, 50));
    water.setPosition(0, 400);
    water.setFillColor(sf::Color::Blue);

    // time
    sf::Clock clock;

    CollisionType collision = CollisionType::Idle;
    bool isDead = false;
    bool isCoinVisible = true;
    int coinCnt = 0;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        collision = CollisionType::Idle;
        isDead = false;

        // 이동
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(-speed * dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(speed * dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.move(0.f, -speed * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player.move(0.f, speed * dt);
        }
        // 차량 충돌
        if (isColliding(player.getGlobalBounds(), car.getGlobalBounds())) {
            collision = CollisionType::Vehicle;
            isDead = true;
            std::cout << "차량에 부딪혔습니다.\n";
        // 익사
        } else if (isColliding(player.getGlobalBounds(), water.getGlobalBounds())) {
            collision = CollisionType::Drowned;
            isDead = true;
            std::cout << "물에 빠졌습니다.\n";
        // 코인
        } else if (isCoinVisible && isColliding(player.getGlobalBounds(), coin.getGlobalBounds())) {
            collision = CollisionType::CoinCollected;
            coinCnt++;
            isCoinVisible = false;
            std::cout << "코인을 획득했습니다. 현재 코인 수는 " << coinCnt << "개입니다.\n";
        }

        window.clear();

        window.draw(player);
        window.draw(car);
        if (isCoinVisible) {
            window.draw(coin);
            window.draw(text);
        }
        window.draw(water);

        window.display();

        if (isDead) {
            // dead 처리
            break;
        }
    }

    return 0;
}