#pragma once

#include <SFML/Graphics.hpp>
#include "rigidbody.h"

class GameObject {
public:
    Rigidbody rigidbody;
    sf::Shape* shape;
    bool active;

    GameObject();
    virtual ~GameObject();

    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};