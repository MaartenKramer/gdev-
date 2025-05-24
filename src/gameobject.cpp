#include "..\\include\\gameobject.h"

GameObject::GameObject() : active(true), shape(nullptr) {}

GameObject::~GameObject() {
    if (shape) delete shape;
}

void GameObject::update(float deltaTime) {
    rigidbody.update(deltaTime);
    if (shape) {
        shape->setPosition(rigidbody.position.x, rigidbody.position.y);
    }
}

void GameObject::render(sf::RenderWindow& window) {
    if (active && shape) {
        window.draw(*shape);
    }
}

sf::FloatRect GameObject::getBounds() const {
    if (shape) {
        return shape->getGlobalBounds();
    }
    return sf::FloatRect();
}