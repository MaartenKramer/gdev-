#pragma once

#include "vector2.h"

class Rigidbody {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;
    float drag;

    Rigidbody(float mass = 1.0f, float drag = 0.01f);

    void addForce(const Vector2& force);
    void update(float deltaTime);
};