#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <vector>
#include "vec3.h"
using namespace std;

class CelestialBody
{
public:
    vec3 position;
    vec3 velocity;
    vec3 force;
    double mass;
    /*
    vector<vector<vector<double>>> force_vector;
    vector<vector<vector<double>>> position_vector;
    vector<vector<vector<double>>> velocity_vector;
    */
    vector<vec3> force_vector;

    //3D vectors work like this: velocity_vector[0][0][0] = 1 <- all elements in first row are 1. Kinda like numpy :)



    CelestialBody(vec3 position, vec3 velocity, double mass);
    CelestialBody(double x, double y, double z, double vx, double vy, double vz, double mass);
    void resetForce();
};

#endif // CELESTIALBODY_H
