#include <iostream>
#include <cmath>
#include <cstdlib>
#include "solarsystem.h"
#include "solver.h"
#include <string>
using namespace std;

void testing_main();

int main(int numArguments, char **arguments)
{
    if (strcmp(arguments[1],"Test")){
        testing_main();
    }
    else{
    int numTimesteps = 1e5;
    string solvertype = "Verlet";
    if(numArguments >= 3){
        numTimesteps = atoi(arguments[1]);
        solvertype = (arguments[2]);
    }
        SolarSystem solarSystem;
        // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
        // This can then be used to modify properties or print properties of the body if desired
        // Use with: solarSystem.createCelestialBody( position, velocity, mass );

        solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");

        // We don't need to store the reference, but just call the function without a left hand side
        // WE SHOULD ADD A NAME FOR THE OBJECTS?
        solarSystem.createCelestialBody( vec3(-1.752200603881933E-01, 9.675633320786794E-01,-3.799746898985921E-05), vec3(-1.720124877602163E-02*365,-3.130282140938300E-03*365,-2.538590515321615E-07*365), 3e-6, "Earth" );
        //    solarSystem.createCelestialBody( vec3(-4.261270488543623E+00, -3.367325372481964E+00, 1.093347180153562E-01), vec3(4.592148015424783E-03*365, -5.569898451309285E-03*365, -7.959975748130483E-05*365), 1.9/2*1e-3, "Jupiter");
        //    solarSystem.createCelestialBody(vec3(-1.583672712165000E+00,-3.890283228691061E-01, 3.071411265610202E-02), vec3(3.860856746782269E-03,-1.239426308079003E-02,-3.544723197396996E-04)*365, 3.3e-7, "Mars");
        //    solarSystem.createCelestialBody( vec3(-3.877081979511674E-01,-7.784734690816700E-03,3.493213369519331E-02), vec3(-5.288319535531131E-03,-2.691956351115996E-02,-1.714528496530611E-03)*356, 1.65e-7,"Mercury");
        //    solarSystem.createCelestialBody(vec3(7.112895540792180E-02,-7.236895081570862E-01,-1.403169883793853E-02), vec3(1.999285129672666E-02,1.906111736867988E-03,-1.127570469009755E-03)*365,2.45e-6,"Venus");
        //    solarSystem.createCelestialBody(vec3(2.867982421897927E+01,-8.597788775778826E+00,-4.839477920436837E-01), vec3(8.861308537273553E-04,3.020669017964271E-03,-8.309848039026806E-05)*365,5.55e-5, "Uranus");



        //TRY WITH OTHER INITIAL CONDITIONS
        //solarSystem.createCelestialBody( vec3(-2, 0, 0.), vec3(0, -1.569898451309285E-03*365, 0), 3e-4 );
        //solarSystem.createCelestialBody( vec3(1., 0., 0.), vec3(0, -2*M_PI, 0), (1.9/2)*1e-3 );

        // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
        vector<CelestialBody> &bodies = solarSystem.bodies();

        for(int i = 0; i<bodies.size(); i++) {
            CelestialBody &body = bodies[i]; // Reference to this body
            cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
        }

        double dt = 0.001;
        Solver integrator(dt, numTimesteps);
        if (solvertype == "Euler"){
            integrator.Euler(solarSystem);
        }
        if(solvertype == "Verlet"){
            integrator.Verlet(solarSystem);
        }

        //WRITE TO FILE
        solarSystem.writeToFile(solvertype);
        cout << "I just created my first solar system that has " << solarSystem.bodies().size() << " objects." << endl;
    }
    return 0;
}
