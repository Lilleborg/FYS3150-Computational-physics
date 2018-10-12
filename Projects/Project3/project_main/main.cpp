#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "solarsystem.h"
#include "euler.h"

using namespace std;

int main(int argc, char* argv[])
{
   int N = atoi(argv[1]);
    return 0;

    SolarSystem solarSystem;
    //CREATING SOLAR SYSTEM

    PlanetaryObject &sun = solarSystem.createPlanetaryObject( vec3(0,0,0), vec3(0,0,0), 1.0); //Create the sun

    vector<PlanetaryObject> $objects = solarSystem.objects(); //Gets no. of bodies in object solarSystem AT END OF NO OF OBJECTS

    //Finds initial positions of planets
    for(int i=0; i < objects.size(); i++){
        PlanetaryObject &object = objects[i];
        cout << "The position of this object is " << object.position << " with velocity " << object.velocity << endl;
    }

    //INTEGRATION
    double dt = 0.001;

    Euler integrator(dt);
    for(int tstep=0; tstep < NumTimeSteps; tstep++){
        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile("output.txt");
    }
}
