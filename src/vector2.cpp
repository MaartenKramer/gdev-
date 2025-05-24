#include "..\\include\\vector2.h"

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const {
    float mag = magnitude();
    if (mag > 0) {
        return Vector2(x / mag, y / mag);
    }
    return Vector2();
}