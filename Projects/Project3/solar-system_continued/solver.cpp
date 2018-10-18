#include "solver.h"
#include "solarsystem.h"

Solver::Solver(double dt) :
    m_dt(dt)
{
}
/*
void Solver::Euler(SolarSystem &system)
{
    system.calculateForcesAndEnergy();

    for(CelestialBody &body : system.bodies()) {
        body.position += body.velocity*m_dt;
        body.velocity += body.force / body.mass * m_dt;
    }
}
*/

void Solver::Euler(SolarSystem &system)
{

    for (int i=0; i<SolarSystem::steps; i++){
        system.calculateForcesAndEnergy();
        for(CelestialBody &body : system.bodies()) {
            body.position += body.velocity*m_dt;
            body.position_vector.push_back(body.position);
            body.velocity += body.force / body.mass * m_dt;
            body.velocity_vector.push_back(body.velocity);


        }
    }
}

void Solver::Verlet(SolarSystem &system)
{
    system.calculateForcesAndEnergy();

    for(CelestialBody &body : system.bodies()) {
        body.position += m_dt*body.velocity + (m_dt*m_dt)*0.5*body.force;
        body.velocity += m_dt*0.5*(body.force + body.force); //how do we deal with indices here :(
    }
}

/*
void Solver::Verlet(SolarSystem &system)
{
    system.calculateForcesAndEnergy();

    for(CelestialBody &body : system.bodies()) {
        body.position += m_dt*body.velocity + (m_dt*m_dt)*0.5*body.force;
        body.velocity += m_dt*0.5*(body.force + body.force); //how do we deal with indices here :(
    }
}
*/

