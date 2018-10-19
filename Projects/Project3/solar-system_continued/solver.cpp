#include "solver.h"
#include "solarsystem.h"
#include <iostream>

Solver::Solver(double dt, double steps) :
    m_dt(dt), m_steps(steps)
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

    for (int i=0; i< m_steps; i++){
        system.calculateForcesAndEnergy();
        for(CelestialBody &body : system.bodies()) {
            //cout << " Body cycle " << endl;
            body.position += body.velocity*m_dt;
            body.position_vector.push_back(body.position);
            body.velocity += body.force / body.mass * m_dt;
            //body.velocity_vector.push_back(body.velocity);
            //std::cout << "Update position " << std::endl;
            //body.position.print();
        }
        //system.writeToFile("positions_euler.txt");
    }
}

void Solver::Verlet(SolarSystem &system)
{
    //POSITION OF BODY
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
        //system.writeToFile("positions_verlet.txt");
    }
}
/*
    //VELOCITY OF BODY
    for (int i=0; i<SolarSystem::steps; i++){
        for(CelestialBody &body : system.bodies()) {
            body.velocity += m_dt*0.5*(body.force_vector[i+1] + body.force_vector[i]);
            body.velocity_vector.push_back(body.velocity);
        }
    }
}
*/
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

