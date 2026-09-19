#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Bird.hpp"
#include "PipeHandler.hpp"


enum class GameState {
    Menu,
    Playing,
    GameOver
};

class Game {
private:
    sf::RenderWindow game_window;
    sf::Texture texture;
    sf::Sprite sprite;

    float windowWidth = 800.0f;
    float windowHeight = 600.0f;

    sf::SoundBuffer bgmBuffer;
    sf::Sound bgmSound;

    sf::Clock game_clock;

    bird flappy;
    PipeHandler pipe_handler;

    sf::Font font;
    sf::Text startText;
    sf::Text gameOverText;
    sf::Text scoreText;

    GameState currentState = GameState::Menu;

    void reset() {

        flappy = bird(windowWidth, windowHeight);
        pipe_handler = PipeHandler(windowWidth, windowHeight);
        game_clock.restart();
    }

    void render() {
        game_window.clear();
        game_window.draw(sprite);

        switch (currentState) {
            case GameState::Menu:
                game_window.draw(startText);
                break;

            case GameState::Playing:
                pipe_handler.draw(game_window);
                flappy.draw(game_window);
                game_window.draw(scoreText);
                break;

            case GameState::GameOver:
                pipe_handler.draw(game_window);
                flappy.draw(game_window);
                game_window.draw(gameOverText);
                break;
        }

        game_window.display();
    }


    void player_input() {
        sf::Event event;
        while (game_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game_window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    game_window.close();
                }

                if (currentState == GameState::Menu) {
                    if (event.key.code == sf::Keyboard::Space) {
                        currentState = GameState::Playing;
                    }
                }
                else if (currentState == GameState::Playing) {
                    if (event.key.code == sf::Keyboard::Space) {
                        flappy.flap();
                    }
                }
                else if (currentState == GameState::GameOver) {

                    if (event.key.code == sf::Keyboard::Space) {
                        reset();
                        currentState = GameState::Playing;
                    }
                }
            }
        }
    }

    void update(float deltaTime) {
        flappy.update(deltaTime);
        pipe_handler.update(deltaTime);

        sf::FloatRect birdBounds = flappy.getBounds();
        int score = pipe_handler.countPassed(birdBounds.left);
        scoreText.setString("Score:" + std::to_string(score));

         bool hitPipe = pipe_handler.checkAnyCollision(birdBounds);


        bool hitGround = (birdBounds.top + birdBounds.height) >= windowHeight;
        bool hitCeiling = birdBounds.top <= 0.0f;

        if (hitCeiling||hitGround||hitPipe) {
            std::cout << "Collision Detected! Game Over!\n";
            currentState = GameState::GameOver;
        }
    }

    void textUI() {
        if (!font.loadFromFile("assets/ARIAL.TTF")) {
            std::cout << "Failed to load font!\n";
        }

        startText.setFont(font);
        startText.setString("Press SPACE to start or ESC to exit");
        startText.setCharacterSize(36);
        startText.setFillColor(sf::Color::White);
        sf::FloatRect startBounds = startText.getLocalBounds();
        startText.setOrigin(startBounds.left + startBounds.width / 2.0f,startBounds.top + startBounds.height / 2.0f);
        startText.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);

        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER\nPress SPACE to restart or ESC to exit");
        gameOverText.setCharacterSize(32);
        gameOverText.setFillColor(sf::Color::Red);
        sf::FloatRect goBounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin(goBounds.left + goBounds.width / 2.0f,goBounds.top + goBounds.height / 2.0f);
        gameOverText.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);

        scoreText.setFont(font);
        scoreText.setString("Score:0");
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        sf::FloatRect scoreBounds = scoreText.getLocalBounds();
        scoreText.setOrigin(scoreBounds.left + scoreBounds.width / 2.0f,scoreBounds.top + scoreBounds.height / 2.0f);
        scoreText.setPosition(windowWidth-50, 20);


    }

public:
    Game()
        : game_window(sf::VideoMode({ 800,600 }), "Flappy flappy"),
          flappy(windowWidth, windowHeight),
          pipe_handler(windowWidth, windowHeight)
    {

        game_window.setVerticalSyncEnabled(true);
        if (!texture.loadFromFile("assets/background.png")) {
            std::cout << "background not loaded\n";
        }
        sprite.setTexture(texture);

        sf::Vector2u textureSize = texture.getSize();
        sf::Vector2u windowSize = game_window.getSize();

        float scaleX = (float)windowSize.x / textureSize.x;
        float scaleY = (float)windowSize.y / textureSize.y;
        sprite.setScale(scaleX, scaleY);

        if (bgmBuffer.loadFromFile("assets/ville_seppanen-1_g.ogg")) {
            bgmSound.setBuffer(bgmBuffer);
            bgmSound.setLoop(true);
            bgmSound.play();
        }

        textUI();
    }

    void run() {
        while (game_window.isOpen()) {
            float deltaTime = game_clock.restart().asSeconds();

            player_input();

            if (currentState == GameState::Playing) {
                update(deltaTime);
            }

            render();
        }
    }
};
