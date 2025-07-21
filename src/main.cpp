#include <SFML/Graphics.hpp>
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
    window.setVerticalSyncEnabled(false);

    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setPosition(100, 100);

    sf::RectangleShape car(sf::Vector2f(100, 50));
    car.setPosition(200, 100);

    sf::RectangleShape coin(sf::Vector2f(25, 25));
    coin.setPosition(500, 100);

    sf::RectangleShape water(sf::Vector2f(700, 50));
    water.setPosition(0, 400);

    CollisionType collision = CollisionType::Idle;
    bool isDead = false;
    int coinCnt = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        collision = CollisionType::Idle;
        isDead = false;

        // 이동
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(7.5, 0);
        // 차량 충돌
        if (isColliding(player.getGlobalBounds(), car.getGlobalBounds())) {
            collision = CollisionType::Vehicle;
            isDead = true;
        // 익사
        } else if (isColliding(player.getGlobalBounds(), water.getGlobalBounds())) {
            collision = CollisionType::Drowned;
            isDead = true;
        // 코인
        } else if (isColliding(player.getGlobalBounds(), coin.getGlobalBounds())) {
            collision = CollisionType::CoinCollected;
            coinCnt++;
        }

        window.clear();

        window.draw(player);
        window.draw(car);
        window.draw(coin);
        window.draw(water);

        window.display();

        if (isDead) {
            // dead 처리
            break;
        }
    }

    return 0;
}