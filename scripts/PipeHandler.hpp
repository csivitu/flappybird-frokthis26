#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Pipe.hpp"

class PipeHandler {
private:
    std::vector<Pipe> m_pipes;
    float pipeSpeed = 200.0f;
    float windowWidth;
    float windowHeight;

    float startTimer = 0.0f;
    float startDelay = 3.0f; 
    bool hasSpawnedInitial = false;
    int score = 0;

    std::uniform_int_distribution <int> distr;
    std::mt19937 gen{std::random_device{}()};


    void spawnInitialPipes() {
        for (int i = 0; i < 5; ++i) {
            float xPos = windowWidth + (i * 450.0f);
            float pipeHeight = static_cast<float>(distr(gen));
            float gapHeight = 300.0f;

            m_pipes.emplace_back(xPos, pipeHeight, gapHeight, windowHeight);
        }
    }

public:
    PipeHandler(float windowWidth, float windowHeight) 
        : windowWidth(windowWidth), windowHeight(windowHeight),distr(100,250)
    {
        
        
    }

    void update(float deltaTime) {
        if (!hasSpawnedInitial) {
            startTimer += deltaTime;
            if (startTimer >= startDelay) {
                spawnInitialPipes();
                hasSpawnedInitial = true;
            }
            return; 
        }

        for (auto& pipe : m_pipes) {
            pipe.move(-pipeSpeed * deltaTime, 0.0f);
            if (pipe.markPassed(windowWidth / 4.0f)) {
                ++score;
            }
        }
        if(hasSpawnedInitial){
            float c_speed  = pipeSpeed;
           c_speed = movement(c_speed,deltaTime);
            pipeSpeed = c_speed;
    }
    }

    void draw(sf::RenderWindow& window) {
        for (auto& pipe : m_pipes) {
            pipe.draw(window);
        }
    }

    bool checkAnyCollision(const sf::FloatRect& birdBounds) const {
        for (const auto& pipe : m_pipes) {
            if (pipe.checkCollision(birdBounds)) {
                return true;
            }
        }
        return false;
    }

    int getScore() const {
        return score;
    }
};