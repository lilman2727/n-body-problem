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
    Vector2D force;
    double mass;
    public:
    Body();
    Body(Vector2D pos, double mass);
};


#endif //N_BODY_PROBLEM_BODY_H