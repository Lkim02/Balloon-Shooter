#ifndef BALLOON_H
#define BALLOON_H

#include <SFML/Graphics.hpp>

class Balloon {
public:
    Balloon(float radius, const sf::Vector2u& windowSize);
    const sf::CircleShape& getShape() const;
    void update(float deltaTime);
    bool isOffScreen(const sf::Vector2u& windowSize) const;

private:
    sf::CircleShape shape;
    sf::Vector2f targetPosition;
    sf::Vector2f moveDirection;
    float speed;
};

#endif
