#pragma once
#include "gameobject.h"

class Enemy : public GameObject {
private:
    float horizontalSpeed;
    float verticalSpeed;
    float direction;
    float screenWidth;
    
public:
    Enemy(float x, float y, float size, sf::Color color, float screenWidth);
    void update(float deltaTime) override;
    bool isOffScreen(float screenHeight);
};