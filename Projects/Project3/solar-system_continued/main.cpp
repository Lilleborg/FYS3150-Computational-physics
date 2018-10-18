#include <iostream>
#include <cmath>
#include <cstdlib>
#include "solarsystem.h"
#include "solver.h"
using namespace std;

int main(int numArguments, char **arguments)
{
    int numTimesteps = 10;
    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);

    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0);

    // We don't need to store the reference, but just call the function without a left hand side
    solarSystem.createCelestialBody( vec3(-1.752200603881933E-01, 9.675633320786794E-01,-3.799746898985921E-05), vec3(-1.720124877602163E-02/365,-3.130282140938300E-03/365,-2.538590515321615E-07/365), 3e-6 );
    solarSystem.createCelestialBody( vec3(-4.261270488543623E+00, -3.367325372481964E+00, 1.093347180153562E-01), vec3(4.592148015424783E-03/365, -5.569898451309285E-03/365, -7.959975748130483E-05/365), 1.9/2*1e-3 );
    //solarSystem.createCelestialBody( vec3(-1, 0, 0.), vec3(0, -2*M_PI, 0), 3e-6 );

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    double dt = 0.00001;
    Solver integrator(dt, numTimesteps);
    integrator.Euler(solarSystem);
    //integrator.Verlet(solarSystem);

    //COMMENT FOR SAFETY

    /*
    Solver integrator(dt);
    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.Euler(solarSystem);
        solarSystem.writeToFile("positions.txt");
    }
    */
    cout << "I just created my first solar system that has " << solarSystem.bodies().size() << " objects." << endl;
    return 0;
}

