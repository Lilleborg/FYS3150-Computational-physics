#include <iostream>
#include <cmath>
#include <cstdlib>
#include "solarsystem.h"
#include "solver.h"
using namespace std;

void test_energy(double dt, int numTimesteps);

int main(int numArguments, char **arguments)
{
    int numTimesteps = 10000;
    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);
    //Want a for loop here that loops over different timesteps
    return 0;
}



void test_energy(double dt, int numTimesteps){
    SolarSystem solarSystem;
    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 );
    solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6 );
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }
    Solver integrator(dt);
    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.Euler(solarSystem);
    }
    //Want to check if energy is conserved => energy change is less than some tol
    //If energy is conserved, return for what dt it is conserved
}
