#include "solver.h"
#include "solarsystem.h"
#include <iostream>
#include "celestialbody.h"
#include <math.h>

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
        if(i % int(m_steps/10) == 0){       // saving only 10 steps
            system.kinetic_vector.push_back(system.kineticEnergy());
            system.potential_vector.push_back(system.potentialEnergy());
            system.ang_momentum_vector.push_back(system.angularMomentum());
        }

    }
}

void Solver::Verlet(SolarSystem &system)
{
    for (int i=0; i<m_steps; i++){
        system.calculateForcesAndEnergy();
        for(CelestialBody &body : system.bodies()) {
                vec3 acc = body.force/body.mass;
                body.position_vector.push_back(body.position);  // adding current position to vector
                rlength = body.position.length();               // length of current position
                body.position += m_dt*body.velocity + (m_dt*m_dt)*0.5*acc;      // next position
                // perihelion calculation adjustments
                if (body.name == "Mercury" && i > 2){
                    if (rlength<body.position_vector.end()[-2].length() && rlength < body.position.length()){  // testing for rlength smaller than previous step and next step
                        body.peri_angl_vector.push_back(get_perihelion_precession(body.position_vector.back()));
                    }
                }
                vec3 acc2;
                acc2.copy(acc);
                system.calculateForcesAndEnergy();
                body.velocity += m_dt*0.5*(body.force/body.mass + acc2);

        if(i % int(m_steps/10) == 0){       // saving only 10 steps
            system.kinetic_vector.push_back(system.kineticEnergy());
            system.potential_vector.push_back(system.potentialEnergy());
            system.ang_momentum_vector.push_back(system.angularMomentum());
        }

    } // time end
}}
void Solver::Verlet_perihelion(SolarSystem &system)
{
    for (int i=0; i<m_steps; i++){
        system.calculateForcesAndEnergy_GR();
        for(CelestialBody &body : system.bodies()) {
            if (body.name != "Sun"){
                vec3 acc = body.force/body.mass;
                body.position_vector.push_back(body.position);  // adding current position to vector
                rlength = body.position.length();               // length of current position
                body.position += m_dt*body.velocity + (m_dt*m_dt)*0.5*acc;      // next position
                // perihelion calculation adjustments
                if (body.name == "Mercury" && i > 2){
                    if (rlength<body.position_vector.end()[-2].length() && rlength < body.position.length()){  // testing for rlength smaller than previous step and next step
                        body.peri_angl_vector.push_back(get_perihelion_precession(body.position_vector.back()));
                    }
                }
                vec3 acc2;
                acc2.copy(acc);
                system.calculateForcesAndEnergy_GR();
                body.velocity += m_dt*0.5*(body.force/body.mass + acc2);

            }} // bodies end
        if(i % int(m_steps/10) == 0){       // saving only 10 steps
            system.kinetic_vector.push_back(system.kineticEnergy());
            system.potential_vector.push_back(system.potentialEnergy());
            system.ang_momentum_vector.push_back(system.angularMomentum());
        }

    } // time end
}
double Solver::get_perihelion_precession(vec3 position) const{
    // private method for finding perihelion angle used in 3g)
    return atan2(position.y(),position.x());
}
