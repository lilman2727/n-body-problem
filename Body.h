//
// Created by 004ha on 06.08.2026.
//

#ifndef N_BODY_PROBLEM_BODY_H
#define N_BODY_PROBLEM_BODY_H
#include "Vector2D.h"

class Body
{
    int id;
    Vector2D pos;
    Vector2D vel;
    Vector2D acc;
    double mass;
    public:
    Body();
    Body(Vector2D pos, double mass) : pos(pos), mass(mass) {};
    double getMass() const { return this->mass; }
    void setMass(double mass) { this->mass = mass; }
    Vector2D getPos() const { return this->pos; }
    void setPos(Vector2D pos) { this->pos = pos; }
    Vector2D getVel() const { return this->vel; }
    void setVel(Vector2D vel) { this->vel = vel; }
    Vector2D getAcc() const { return this->acc; }
    void setAcc(Vector2D force) { this->acc = force; }

    bool operator==(const Body& rhs) const { return id == rhs.id; }
    bool operator!=(const Body& rhs) const { return id != rhs.id; }
};


#endif //N_BODY_PROBLEM_BODY_H