#include "Vector2D.h"

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float value) const {
    return Vector2D(x * value, y * value);
}

Vector2D Vector2D::operator/(float value) const {
    return Vector2D(x / value, y / value);
}

bool Vector2D::operator==(const Vector2D& other) const
{
    return (x == other.x) && (y == other.y);
}

float Vector2D::length() const {
    return std::sqrt(x * x + y * y);
}

void Vector2D::normalize() {
    float len = length();
    if (len > 0) {
        x /= len;
        y /= len;
    }
}

float Vector2D::operator*(const Vector2D& other) const {
    return x * other.x + y * other.y;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2D Vector2D::lerp(const Vector2D& a, const Vector2D& b, float factor) const {
    return a + (b - a) * factor;
}
Vector2D& Vector2D::zero()
{
    this->x = 0;
    this->y = 0;
    return *this;
}
