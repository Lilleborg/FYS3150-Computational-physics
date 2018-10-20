#include "solver.h"
#include "solarsystem.h"
#include <iostream>

Solver::Solver(double dt, double steps) :
    m_dt(dt), m_steps(steps)
{

}
void Solver::Euler(SolarSystem &system)
{
    for (int i=0; i< m_steps; i++){
        system.calculateForcesAndEnergy();
        for(CelestialBody &body : system.bodies()) {
            body.position += body.velocity*m_dt;
            body.position_vector.push_back(body.position);
            body.velocity += (body.force / body.mass) * m_dt;
        }
    }
}

void Solver::Verlet(SolarSystem &system)
{
    for (int i=0; i<m_steps; i++){
        system.calculateForcesAndEnergy();
        for(CelestialBody &body : system.bodies()) {
            vec3 acc = body.force/body.mass;
            body.position += m_dt*body.velocity + (m_dt*m_dt)*0.5*acc;
            body.position_vector.push_back(body.position);
            vec3 acc2;
            acc2.copy(acc);
            system.calculateForcesAndEnergy();
            body.velocity += m_dt*0.5*(body.force/body.mass + acc2);
            //body.velocity_vector.push_back(body.velocity);
        }
    }
}
