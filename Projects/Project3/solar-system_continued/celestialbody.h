#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <vector>
#include "vec3.h"
#include <string>
using namespace std;

class CelestialBody
{
public:
    vec3 position;
    vec3 velocity;
    vec3 force;
    double mass;
    string name;
    vector<vec3> position_vector;

    //3D vectors work like this: velocity_vector[0][0][0] = 1 <- all elements in first row are 1. Kinda like numpy :)

    CelestialBody(vec3 position, vec3 velocity, double mass,string name);
    CelestialBody(double x, double y, double z, double vx, double vy, double vz, double mass);
    void resetForce();
};

#endif // CELESTIALBODY_H
