#include "Balloon.h"
#include <cstdlib>
#include <cmath>

Balloon::Balloon(float radius, const sf::Vector2u& windowSize) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);

    
    int side = rand() % 4;
    switch (side) {
    case 0: 
        shape.setPosition(0, rand() % windowSize.y);
        break;
    case 1: 
        shape.setPosition(windowSize.x, rand() % windowSize.y);
        break;
    case 2: 
        shape.setPosition(rand() % windowSize.x, 0);
        break;
    case 3: 
        shape.setPosition(rand() % windowSize.x, windowSize.y);
        break;
    }

    
    targetPosition = sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f);

   
    sf::Vector2f direction = targetPosition - shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    moveDirection = direction / length;  
    speed = 700.0f + static_cast<float>(std::rand() % 100); 
}

const sf::CircleShape& Balloon::getShape() const {
    return shape;
}

void Balloon::update(float deltaTime) {
   
    shape.move(moveDirection * speed * deltaTime);
}

bool Balloon::isOffScreen(const sf::Vector2u& windowSize) const {
    return shape.getPosition().x < -shape.getRadius() * 2 ||
        shape.getPosition().x > windowSize.x + shape.getRadius() * 2 ||
        shape.getPosition().y < -shape.getRadius() * 2 ||
        shape.getPosition().y > windowSize.y + shape.getRadius() * 2;
}
