#include "..\\include\\enemy.h"

Enemy::Enemy(float x, float y, float size, sf::Color color, float screenWidth)
    : screenWidth(screenWidth) {
    
    // Makes enemy shape
    shape = new sf::RectangleShape(sf::Vector2f(size, size));
    shape->setFillColor(color);
    shape->setOrigin(size / 2, size / 2);
    rigidbody.position = Vector2(x, y);
    shape->setPosition(x, y);
    
    // Rigidbody values
    rigidbody.mass = 0.5f;
    rigidbody.drag = 0.1f;
    
    // Enemy speed
    horizontalSpeed = 100.0f;
    verticalSpeed = 500.0f;
    
    //Decides at what angle the enemy moves
    direction = (rand() % 2 == 0) ? -1.0f : 1.0f;

    //Movement calculation
    rigidbody.velocity = Vector2(direction * horizontalSpeed, verticalSpeed);
}

void Enemy::update(float deltaTime) {
    GameObject::update(deltaTime);
}

// Checks if enemy has moved offscreen
bool Enemy::isOffScreen(float screenHeight) {
    float halfHeight = ((sf::RectangleShape*)shape)->getSize().y / 2;
    return rigidbody.position.y > screenHeight + halfHeight;
}