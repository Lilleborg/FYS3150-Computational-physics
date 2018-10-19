#include "solarsystem.h"
#include <iostream>
using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0)
{
}

CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass) {
    m_bodies.push_back( CelestialBody(position, velocity, mass) );
    return m_bodies.back(); // Return reference to the newest added celstial body
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
    //cout << "START" << endl;
    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            vec3 force = (GM_star*body2.mass*deltaRVector)/pow(dr,3);
            body1.force += force;
            body2.force -= force;

            //cout << "body1 = " << body1.force << "body2 = " << body2.force << endl;
            //deltaRVector.print();
            //cout << "----------" << i << "    " << j << endl;
            //body1.force_vector.push_back(body1.force);
            //body2.force_vector.push_back(body2.force);
        }

        //JUST THE EXPRESSIONS
        /*
        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();
        m_potentialEnergy -= GM_star*body1.mass/body1.position.length();
        m_angularMomentum = body2.mass*(cross(body2.position body2.velocity));
        */

    }
}

void SolarSystem::writeToFile()
{   int i = 1;
    for (CelestialBody &body: m_bodies)
    {
        vector<vec3> file = body.position_vector;
        string i_string = to_string(i);
        string filename = "positions" + i_string + ".txt";
        ofstream outFile(filename);

        for (const auto &e : file) outFile << e.x() << " " << e.y() <<  " " << e.z() << "\n";
        i++;
    }
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

/*
void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    //m_file << numberOfBodies() << endl;
    //m_file << "Comment line that needs to be here. Balle." << endl;
    for(CelestialBody &body : m_bodies) {
        m_file << body.position.x() << "  " << body.position.y() << "  " << body.position.z() << "\n";
    }
}
*/


vec3 SolarSystem::angularMomentum() const
{
    return m_angularMomentum;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
