#pragma once
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

class bird {
private:
    sf::Vector2f spawnPosition;

    inline static sf::Texture texture;
    sf::Sprite sprite;

    float vel = 0.0f;
    float gravity = 1200.0f;
    float accel = 0.0f;
public:
    bird(float windowWidth, float windowHeight) {
        if (!texture.loadFromFile("assets/spaceship.png")) {
            std::cout << "Error loading spaceship texture!\n";
        }
        sprite.setTexture(texture);

        sf::Vector2u size = texture.getSize();
        sprite.setOrigin((size.x) / 2.0f, (size.y) / 2.0f);

        sprite.setScale(1.5f, 1.5f);

        spawnPosition = sf::Vector2f(windowWidth / 4.0f, windowHeight / 2.0f);
        sprite.setPosition(spawnPosition.x, spawnPosition.y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
    void flap() {
        if (vel >= gravity / 10.0f) {
            accel = 0.0f;
            vel = -gravity / 4.0f;
        }
    }
    void update(float deltaTime) {
        accel += gravity * deltaTime;

        if (accel >= gravity) {
            accel = gravity;
        }

        vel += accel * deltaTime;
        spawnPosition.y += vel * deltaTime;

        sprite.setPosition(spawnPosition.x, spawnPosition.y);

        float targetRotation = 90.0f + (vel * 0.08f);
        targetRotation = std::clamp(targetRotation, 45.0f, 135.0f);

        sprite.setRotation(targetRotation);
    }

    sf::FloatRect getBounds() const {
        float size= 53.0f;
        float half= 26.5f;
        float centerX= sprite.getPosition().x;
        float centerY= sprite.getPosition().y;
        float left= centerX-half;
        float top= centerY-half;
        sf::FloatRect box(left, top, size, size);
        return box;
    }
};

float moves(float pace, float deltaTime){

    pace += 2*5.0f*deltaTime;
        if (pace > 450.0f){
            pace=450.0f;
        }

    return pace;
}
