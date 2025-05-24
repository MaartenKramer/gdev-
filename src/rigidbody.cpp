#include "..\\include\\rigidbody.h"

Rigidbody::Rigidbody(float mass, float drag)
    : mass(mass), drag(drag) {}

void Rigidbody::addForce(const Vector2& force) {
    Vector2 resultingAcceleration = force * (1.0f / mass);
    acceleration += resultingAcceleration;
}

void Rigidbody::update(float deltaTime) {
    // Adds drag
    Vector2 dragForce = velocity * -drag;
    addForce(dragForce);

    // Updates velocity with acceleration
    velocity += acceleration * deltaTime;

    // Updates position with velocity
    position += velocity * deltaTime;

    // Resets acceleration
    acceleration = Vector2(0.0f, 0.0f);
}