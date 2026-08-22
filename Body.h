//
// Created by 004ha on 06.08.2026.
//

#ifndef N_BODY_PROBLEM_BODY_H
#define N_BODY_PROBLEM_BODY_H
#include "Vector2D.h"

class Body
{
    Vector2D pos;
    Vector2D vel;
    Vector2D acc;
    double mass;
    public:
    Body();
    Body(Vector2D pos, double mass, int red, int green, int blue) : pos(pos), mass(mass), RED(red), GREEN(green), BLUE(blue) {};
    int RED;
    int GREEN;
    int BLUE;
    double getMass() const { return this->mass; }
    void setMass(double mass) { this->mass = mass; }
    Vector2D getPos() const { return this->pos; }
    void setPos(Vector2D pos) { this->pos = pos; }
    Vector2D getVel() const { return this->vel; }
    void setVel(Vector2D vel) { this->vel = vel; }
    Vector2D getAcc() const { return this->acc; }
    void setAcc(Vector2D force) { this->acc = force; }


    bool operator==(const Body& rhs) const { return this == &rhs; }
    bool operator!=(const Body& rhs) const { return this != &rhs; }
};


#endif //N_BODY_PROBLEM_BODY_H