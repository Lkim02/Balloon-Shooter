#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Balloon.h"

void handleEvents(sf::RenderWindow& window, std::vector<Balloon>& balloons);
void updateBalloons(std::vector<Balloon>& balloons, float deltaTime, const sf::Vector2u& windowSize);
void render(sf::RenderWindow& window, const sf::Sprite& backgroundSprite, const std::vector<Balloon>& balloons);

int main() {
    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Balloon Game");

    
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        std::cerr << "Error loading background image!" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("music2.ogg")) {
        std::cerr << "Error loading music!" << std::endl;
        return -1;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    std::vector<Balloon> balloons;
    sf::Clock spawnClock;
    sf::Clock deltaClock;

    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();

        handleEvents(window, balloons);

        if (spawnClock.getElapsedTime().asSeconds() > 2.0f) {
            balloons.emplace_back(20.f, window.getSize());
            spawnClock.restart();
        }

        updateBalloons(balloons, deltaTime, window.getSize());

        render(window, backgroundSprite, balloons);
    }

    return 0;
}

void handleEvents(sf::RenderWindow& window, std::vector<Balloon>& balloons) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                for (size_t i = 0; i < balloons.size(); ++i) {
                    if (balloons[i].getShape().getGlobalBounds().contains(mousePos)) {
                        balloons.erase(balloons.begin() + i);
                        break;
                    }
                }
            }
        }
    }
}

void updateBalloons(std::vector<Balloon>& balloons, float deltaTime, const sf::Vector2u& windowSize) {
    for (size_t i = 0; i < balloons.size();) {
        balloons[i].update(deltaTime);
        if (balloons[i].isOffScreen(windowSize)) {
            balloons.erase(balloons.begin() + i);
        }
        else {
            ++i;
        }
    }
}

void render(sf::RenderWindow& window, const sf::Sprite& backgroundSprite, const std::vector<Balloon>& balloons) {
    window.clear();
    window.draw(backgroundSprite);
    for (const auto& balloon : balloons) {
        window.draw(balloon.getShape());
    }
    window.display();
}
