#include "..\\include\\player.h"

Player::Player(float x, float y, float radius, sf::Color color)
    : radius(radius), moveForce(2000.0f) {
    
    // Make player circle
    shape = new sf::CircleShape(radius);
    shape->setFillColor(color);
    shape->setOrigin(radius, radius);

    // Set initial position
    rigidbody.position = Vector2(x, y);
    shape->setPosition(x, y);

    // Rigidbody values
    rigidbody.mass = 1.0f;
    rigidbody.drag = 5.0f;
}

// Player movement controls
void Player::handleInput(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rigidbody.addForce(Vector2(-moveForce, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rigidbody.addForce(Vector2(moveForce, 0));
    }
}

void Player::update(float deltaTime) {
    GameObject::update(deltaTime);
}

// Prevents player from leaving screen
void Player::constrainToScreen(float screenWidth) {
    if (rigidbody.position.x < radius) {
        rigidbody.position.x = radius;
        rigidbody.velocity.x = 0;
    }
    else if (rigidbody.position.x > screenWidth - radius) {
        rigidbody.position.x = screenWidth - radius;
        rigidbody.velocity.x = 0;
    }
}