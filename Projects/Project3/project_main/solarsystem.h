#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H



#include "planetaryobject.h"
#include <vector>
#include <string>
#include <fstream>

class SolarSystem
{
public:
    SolarSystem();
    PlanetaryObject &createPlanetaryObject(vec3 position, vec3 velocity, double mass); //Function creating a celestial object through PlanetaryObject

    int NoOfObjects() const;

    double TotalEnergy() const;
    double PotentialEnergy() const;
    double KineticEnergy() const;

    void WriteToFile(std::string filename);
    std::vector<PlanetaryObject> &objects;

private:
    std::vector<PlanetaryObject> &m_objects;
    vec3 m_angularMomentum;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
};

#endif // SOLARSYSTEM_H
