#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

class SolarSystem
{
public:
    SolarSystem();
    CelestialBody &createCelestialBody(vec3 position, vec3 velocity, double mass,string name);
    void calculateForcesAndEnergy();
    int numberOfBodies() const;

    double totalEnergy() const;
    double potentialEnergy() const;
    double kineticEnergy() const;
    void writeToFile(string solver);
    vec3 angularMomentum() const;
    std::vector<CelestialBody> &bodies();
    std::vector<double> kinetic_vector;
    std::vector<double> potential_vector;
    std::vector<vec3> ang_momentum_vector;

private:
    std::vector<CelestialBody> m_bodies;
    vec3 m_angularMomentum;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    double const GM_star = 4*M_PI*M_PI;
};

#endif // SOLARSYSTEM_H
