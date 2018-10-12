#include "solarsystem.h"
#include <iostream>
using namespace std;

SolarSystem::SolarSystem(){

}

//APPEND NEW PLANETARY OBJECT TO "m_objects" LIST
PlanetaryObject &SolarSystem::createPlanetaryObject(vec3 position, vec3 velocity, double mass)
{
    m_objects.push_back( PlanetaryObject(position, velocity, mass) ); //add newest object to list m_objects
    return m_objects.back(); //return last object added to list
}

void SolarSystem::calculateForceEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    for(PlanetaryObject &object : m_objects) {
        //Reset forces on all objects
        object.force.zeros();
    }

}

int SolarSystem::NoOfObjects() const
{
    return m_objects.size();
}
int SolarSystem::TotalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}
int SolarSystem::KineticEnergy() const
{
    return m_kineticEnergy;
}
vec3 SolarSystem::AngularMomentum() const
{
    return m_angularMomentum;
}

std::vector<PlanetaryObject> &SolarSystem::objects()
{
    return m_objects;
}
