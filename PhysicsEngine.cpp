//
// Created by 004ha on 20.08.2026.
//

#include "PhysicsEngine.h"
#include <cmath>

Vector2D calculatePosVector(const Body& first, const Body& second)
{
    return second.getPos() - first.getPos();
}

Vector2D PhysicsEngine::calculateNewtonForce(const Body& first, const Body& second)
{
    if (first == second){return {0, 0};}
    Vector2D vec_r = calculatePosVector(first, second);
    double r_sq = vec_r.getX() * vec_r.getX() + vec_r.getY() * vec_r.getY();
    double r = std::sqrt(r_sq + epsilon * epsilon);
    double f = (G * first.getMass() * second.getMass()) / (r * r * r);

    return f * vec_r;
}

void PhysicsEngine::step(double dt)
{
    // Calculating new positions of bodies
    for (Body& body : bodies)
    {
        Vector2D new_pos = body.getPos() + body.getVel() * dt + body.getAcc() * (dt * dt * 0.5);
        body.setPos(new_pos);
    }

    // Calculating the individual forces on the bodies
    for (Body& body1 : bodies)
    {
        Vector2D force = Vector2D(0, 0);

        for (const Body& body2 : bodies)
        {
            if (body1 != body2)
            {
                force += calculateNewtonForce(body1, body2);
            }
        }
        Vector2D new_acc = force / body1.getMass();
        Vector2D new_vel = body1.getVel() + (body1.getAcc() + new_acc)*(dt*0.5);
        body1.setVel(new_vel);
        body1.setAcc(new_acc);

    }
}


