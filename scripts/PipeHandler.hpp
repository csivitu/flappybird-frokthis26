#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include "Pipe.hpp"

class PipeHandler {
private:
    std::vector<Pipe> m_pipes;
    float pipeSpeed = 200.0f;
    float windowWidth;
    float windowHeight;
    float spawnTimer = 0.0f;
    float spawnInterval = 1.6f;

    std::uniform_int_distribution<int> distr;
    std::mt19937 gen{std::random_device{}()};

    void spawnPipe() {
        float pipeHeight = static_cast<float>(distr(gen));
        float gapHeight = 300.0f;
        float xPos = windowWidth + 50.0f;

        if (!m_pipes.empty()) {
            xPos = m_pipes.back().getX() + 260.0f;
        }

        m_pipes.emplace_back(xPos, pipeHeight, gapHeight, windowHeight);
    }

public:
    PipeHandler(float windowWidth, float windowHeight)
        : windowWidth(windowWidth), windowHeight(windowHeight), distr(100, 250) {}

    void update(float deltaTime) {
        spawnTimer += deltaTime;

        if (m_pipes.empty() || spawnTimer >= spawnInterval) {
            spawnPipe();
            spawnTimer = 0.0f;
        }

        for (auto& pipe : m_pipes) {
            pipe.move(-pipeSpeed * deltaTime, 0.0f);
        }

        m_pipes.erase(
            std::remove_if(m_pipes.begin(), m_pipes.end(), [](const Pipe& pipe) {
                return pipe.getX() + pipe.getWidth() < 0.0f;
            }),
            m_pipes.end());

        pipeSpeed = movement(pipeSpeed, deltaTime);
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
};