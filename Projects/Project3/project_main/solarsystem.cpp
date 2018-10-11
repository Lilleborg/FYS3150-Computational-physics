#include "solarsystem.h"
#include <iostream>
using namespace std;

SolarSystem::SolarSystem(){

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
std::vector<PlanetaryObject> &SolarSystem::object()
{
    return m_objects;
}
