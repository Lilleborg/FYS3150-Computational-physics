#include "euler.h"
#include "solarsystem.h"

Euler::Euler(double dt){
    m_dt = dt;
}

void Euler::IntegrateOneStep(SolarSystem &system){

    system.Force_and_Energy();

    for(PlanetaryObject &object : system.objects()) {
        object.position += object.velocity*m_dt;
        object.velocity += object.force / object.mass * m_dt; //Maybe remove m_dt and only use dt?

    }
}


