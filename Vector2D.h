//
// Created by 004ha on 06.08.2026.
//

#ifndef N_BODY_PROBLEM_VECTOR2D_H
#define N_BODY_PROBLEM_VECTOR2D_H

#include <cmath>

class Vector2D
{
    double x, y;
    public:
    Vector2D() : x(0.0), y(0.0) {};
    Vector2D(double pos_x, double pos_y) : x(pos_x), y(pos_y) {}
    double getX() const { return x; }
    double getY() const { return y; }
    Vector2D operator+(const Vector2D& other) const {return {x+other.x, y+other.y};}
    Vector2D operator-() const {return {-x,-y};}
    Vector2D operator-(const Vector2D& other) const {return {x-other.x, y-other.y};}
    Vector2D operator+=(const Vector2D& other) {return {x+=other.x, y+=other.y};}
    Vector2D operator/(double d) const {return {x/d, y/d};}


    template <typename T>
    Vector2D operator*(T scalar) const {return {x*scalar, y*scalar};}
};

template <typename T>
Vector2D operator*(T scalar, const Vector2D& vec)
{
    return vec*scalar;
}
#endif //N_BODY_PROBLEM_VECTOR2D_H