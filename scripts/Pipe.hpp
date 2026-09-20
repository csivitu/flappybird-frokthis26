#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.hpp"

class Pipe {
private:
    sf::RectangleShape topPipe;
    sf::RectangleShape bottomPipe;

public:
    Pipe(float xPos, float pipeHeight, float gapHeight, float windowHeight) {
        topPipe.setSize(sf::Vector2f(80.0f, pipeHeight));
        topPipe.setFillColor(sf::Color::Green);
        topPipe.setPosition(xPos, 0.0f);

        bottomPipe.setSize(sf::Vector2f(80.0f, windowHeight - (pipeHeight + gapHeight)));
        bottomPipe.setFillColor(sf::Color::Green);
        bottomPipe.setPosition(xPos, pipeHeight + gapHeight);
    }

    void move(float offsetX, float offsetY) {
        topPipe.move(offsetX, offsetY);
        bottomPipe.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(topPipe);
        window.draw(bottomPipe);
    }

    bool checkCollision(const sf::FloatRect& birdBounds) const {
        return topPipe.getGlobalBounds().intersects(birdBounds) || 
               bottomPipe.getGlobalBounds().intersects(birdBounds);
    }

    float getX() const {
        return topPipe.getPosition().x;
    }
};

float movement(float speed,float deltaTime){

    speed= speed + 5.0f*deltaTime;
    return speed;
}