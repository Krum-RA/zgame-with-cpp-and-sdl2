#pragma once
#include <cmath>

class Vector2D {
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);

    
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float value) const;
    Vector2D operator/(float value) const;

    Vector2D& operator-=(const Vector2D& other);

    bool operator==(const Vector2D& other) const;

    float length() const;
    void normalize();

    float operator*(const Vector2D& other) const;

    Vector2D lerp(const Vector2D& a, const Vector2D& b, float factor) const;
    Vector2D& zero();    
};
