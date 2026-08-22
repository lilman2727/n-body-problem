//
// Created by 004ha on 20.08.2026.
//

#ifndef N_BODY_PROBLEM_PHYSICSENGINE_H
#define N_BODY_PROBLEM_PHYSICSENGINE_H

#include <vector>

#include "Body.h"



class PhysicsEngine
{

    std::vector<Body> bodies;
    public:
    PhysicsEngine();
    ~PhysicsEngine();
    std::vector<Body> getBodies();
    void step(double dt);
    Vector2D calculateNewtonForce(const Body& first, const Body& second);
    const double G = 6.6743e-11;
    const double epsilon = 1.0; //change depending on scale of simulation
};










#endif //N_BODY_PROBLEM_PHYSICSENGINE_H