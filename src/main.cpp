// 이거 상당히 어려운데요

#include "character/Character.hpp"

int main() {

    sf::RenderWindow window;
    sf::Vector2f screenSize(1200.f, 1200.f);

    sf::Event event;

    Character character= Character(sf::Vector2f(300.f, 300.f));

    window.create(sf::VideoMode(screenSize.x, screenSize.y), "Player");

    sf::Clock clock;

    while (window.isOpen()) {

        float deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            character.move();
        }

        window.clear();
        window.draw(character);
        window.display();

    }
}