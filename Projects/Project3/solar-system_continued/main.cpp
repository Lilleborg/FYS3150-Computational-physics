#include <iostream>
#include <cmath>
#include <cstdlib>
#include "solarsystem.h"
#include "solver.h"
#include <string>
using namespace std;

int testing_main();

int main(int numArguments, char **arguments)
{
    int years = 2;
    string solvertype = "Verlet";

    if(numArguments == 2){  // Test option, if only one cmd given and that is == "Test" testing will run and terminate after
        if (strcmp(arguments[1],"Test") == 0){
            int result = testing_main();
            result = 0;
            return result;
        }}

    if(numArguments >= 3){
        years = atoi(arguments[1]);
        solvertype = (arguments[2]);
    }

    double dt = 1e-5;
    int numTimesteps = ceil(years/dt);
    cout << "Number of time steps " << numTimesteps << endl;

    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );


    // We don't need to store the reference, but just call the function without a left hand side
    // WE SHOULD ADD A NAME FOR THE OBJECTS?
    solarSystem.createCelestialBody( vec3(-1.734173457390217E-01,9.736937590796603E-01,-1.582107821713564E-04), vec3(-1.720709737865684E-02,-3.125258586509626E-03,-1.120932427483096E-07)*365, 3e-6, "Earth" );
    solarSystem.createCelestialBody( vec3(-4.259467773894452E+00,-3.361194945480983E+00,1.092145047021746E-01), vec3(4.586299412789570E-03,-5.564874896880609E-03,-7.945799167252124E-05)*365, 1.9/2*1e-3, "Jupiter");

    solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");

    solarSystem.createCelestialBody(vec3(-1.583672712165000E+00,-3.890283228691061E-01, 3.071411265610202E-02), vec3(3.860856746782269E-03,-1.239426308079003E-02,-3.544723197396996E-04)*365, 3.3e-7, "Mars");
    solarSystem.createCelestialBody( vec3(-3.877081979511674E-01,-7.784734690816700E-03,3.493213369519331E-02), vec3(-5.288319535531131E-03,-2.691956351115996E-02,-1.714528496530611E-03)*356, 1.65e-7,"Mercury");
    solarSystem.createCelestialBody(vec3(7.112895540792180E-02,-7.236895081570862E-01,-1.403169883793853E-02), vec3(1.999285129672666E-02,1.906111736867988E-03,-1.127570469009755E-03)*365,2.45e-6,"Venus");
    solarSystem.createCelestialBody(vec3(2.867982421897927E+01,-8.597788775778826E+00,-4.839477920436837E-01), vec3(8.861308537273553E-04,3.020669017964271E-03,-8.309848039026806E-05)*365,5.55e-5, "Uranus");



    //TRY WITH OTHER INITIAL CONDITIONS
    //solarSystem.createCelestialBody( vec3(-2, 0, 0.), vec3(0, -1.569898451309285E-03*365, 0), 3e-4 );
    //solarSystem.createCelestialBody( vec3(1., 0., 0.), vec3(0, -2*M_PI, 0), (1.9/2)*1e-3 );

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

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
    return 0;
}

int testing_main(){
    cout << "----Testing started----" << endl;
    int success = 0;            // bool variable

    for (int i = 2; i < 7; ++i) {
        vector <vec3> result_E;  // saving result of Eulertest for each dt
        vector <vec3> result_V;  // saving result of Verlettest for each dt
        double dt = 1/pow(10,i);
        int numTimesteps = ceil(2/dt);
        cout << "Testing with " << numTimesteps << " time steps" << endl;
        SolarSystem testsystem_E;   // system for testing Euler
        SolarSystem testsystem_V;   // system for testing Verlet
        // Initiating bodies
        testsystem_E.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");
        testsystem_E.createCelestialBody( vec3(1,0,0), vec3(0,2*M_PI,0), 3e-6, "Earth" );
        testsystem_V.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");
        testsystem_V.createCelestialBody( vec3(1,0,0), vec3(0,2*M_PI,0), 3e-6, "Earth" );

        // Solving each system and writes to file for plotting
        Solver integrator(dt, numTimesteps);
        integrator.Euler(testsystem_E);
        integrator.Verlet(testsystem_V);

        testsystem_E.writeToFile("Euler_testing","_1e-" + to_string(i));
        testsystem_V.writeToFile("Verlet_testing","_1e-" + to_string(i));

        // Testing conservation, testing against initial values
        double tol = 1e-7;
        double initial_kin_E = testsystem_E.kinetic_vector[0];
        double initial_kin_V = testsystem_V.kinetic_vector[0];
        double initial_pot_E = testsystem_E.potential_vector[0];
        double initial_pot_V = testsystem_V.potential_vector[0];
        double initial_ang_mom_modulus_E = testsystem_E.ang_momentum_vector[0].length();
        double initial_ang_mom_modulus_V = testsystem_V.ang_momentum_vector[0].length();
        vec3 equaling = vec3(); // [x = result kinetic, y = result pot, z = result momentum]
        for (u_long k = 0; k < testsystem_E.kinetic_vector.size();k++){ // looping over the size of the saved vectors
            // setting the value in equaling to 1 if the test fails
            // Euler testing
            if (abs(testsystem_E.kinetic_vector[k]-initial_kin_E)>tol){
                equaling.setX(1);
            }
            if (abs(testsystem_E.potential_vector[k]-initial_pot_E)>tol){
                equaling.setY(1);
            }
            if (abs(testsystem_E.ang_momentum_vector[k].length()-initial_ang_mom_modulus_E)>tol){
                equaling.setZ(1);
            }
            //equaling.print("For Euler");
            result_E.push_back(equaling);
            equaling.zeros();   // resetting equaling
            // Verlet testing
            if (abs(testsystem_V.kinetic_vector[k]-initial_kin_V)>tol){
                equaling.setX(1);
            }
            if (abs(testsystem_V.potential_vector[k]-initial_pot_V)>tol){
                equaling.setY(1);
            }
            if (abs(testsystem_V.ang_momentum_vector[k].length()-initial_ang_mom_modulus_V)>tol){
                equaling.setZ(1);
            }
            //equaling.print("For Verlet");
            result_V.push_back(equaling);
            equaling.zeros();
        }
    cout << "With dt = " << dt << endl;
    cout << "For Euler:" << endl;
    for (u_long k = 0; k < result_E.size();k++){ // looping over the size of the saved results
        vec3 result = result_E[k];
        cout << result << " ";
    }
    cout << endl;
    cout << "For Verlet:" << endl;
    for (u_long k = 0; k < result_V.size();k++){ // looping over the size of the saved results
        vec3 result = result_V[k];
        cout << result << " ";
    }
    cout << endl;
    cout << "----Testing ended----" << endl;
    }
    return success;
}
