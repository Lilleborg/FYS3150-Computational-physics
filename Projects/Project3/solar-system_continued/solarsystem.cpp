#include "solarsystem.h"
#include <iostream>
using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0)
{
}
CelestialBody &SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass, string name) {
    // Return reference to the newest added celestial body
    m_bodies.push_back( CelestialBody(position, velocity, mass,name) );
    return m_bodies.back();
}
void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }
    //cout << "START CALCULATING FORCES" << endl;
    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body2.position - body1.position;
            double dr = deltaRVector.length();
            vec3 force = (GM_star*body2.mass*body1.mass*deltaRVector)/pow(dr,3);
            body1.force += force;
            body2.force -= force;
            m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();
            m_potentialEnergy -= GM_star*body2.mass/deltaRVector.length();
            m_angularMomentum = body2.mass*(body2.velocity.cross(body2.position));
        }
    }
}
void SolarSystem::writeToFile(string solver)
{
    for (CelestialBody &body: m_bodies)
    {
        vector<vec3> file = body.position_vector;
        string filename = "./"+ solver + "/" + "positions_" + body.name + ".txt";
        ofstream outFile(filename);
        for (const auto &e : file) outFile << e.x() << " " << e.y() <<  " " << e.z() << "\n";

    }

//    string filename_names = "object_names" + to_string(m_bodies.size()) + ".txt";
//    ofstream outfilename(filename_names);
//    for (const auto &body : m_bodies) outfilename << body.name << "\n";
}
int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}

double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

vec3 SolarSystem::angularMomentum() const
{
    return m_angularMomentum;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
