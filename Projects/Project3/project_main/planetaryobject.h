#ifndef PLANETARYOBJECT_H
#define PLANETARYOBJECT_H

#include "vec3.h"
#include <cstdlib>

using namespace std;

class PlanetaryObject
{
public:
    vec3 position;
    vec3 velocity;
    //vec3 force;
    double mass;
    string name;
    PlanetaryObject(vec3 position, vec3 velocity, double mass, string name);
};

#endif // PLANETARYOBJECT_H
