#pragma once
#include "gameobject.h"

class Player : public GameObject {
private:
    
    float moveForce;
    float radius;
    
public:

    Player(float x, float y, float radius, sf::Color color);
    void handleInput(float deltaTime);
    void update(float deltaTime) override;
    void constrainToScreen(float screenWidth);
};