#include "PhysicsEngine.h"
#include <cmath>
#include <algorithm>

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
    if (!running){return;}
    // Calculating new positions of bodies
    for (Body& body : bodies)
    {
        if (!body.isMovable()) continue;
        Vector2D new_pos = body.getPos() + body.getVel() * dt + body.getAcc() * (dt * dt * 0.5);
        body.setPos(new_pos);
    }

    // Calculating the individual forces on the bodies
    for (Body& body1 : bodies)
    {
        if (!body1.isMovable()) continue;
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

    bodies.erase(
    std::remove_if(bodies.begin(), bodies.end(), [](const Body& b) {
        double x = b.getPos().getX();
        double y = b.getPos().getY();

        return (std::abs(x) > 3*1920 || std::abs(y) > 3*1080);
    }),
    bodies.end()
);
}

void PhysicsEngine::addBody(Body body)
{
    bodies.push_back(body);
}



