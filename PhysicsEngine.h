#ifndef N_BODY_PROBLEM_PHYSICSENGINE_H
#define N_BODY_PROBLEM_PHYSICSENGINE_H

#include <vector>

#include "Body.h"



class PhysicsEngine
{
    bool running = false;
    std::vector<Body> bodies;
    public:
    PhysicsEngine()= default;
    ~PhysicsEngine()= default;
    const std::vector<Body>& getBodies() const { return bodies; }
    void step(double dt);
    void addBody(Body body);
    Vector2D calculateNewtonForce(const Body& first, const Body& second);
    const double G = 6.6743e-11;
    const double epsilon = 1.0; //softening param
    void stop(){this->running = false;}
    void start(){this->running = true;}
    void clearBodies() { bodies.clear(); }

};










#endif //N_BODY_PROBLEM_PHYSICSENGINE_H