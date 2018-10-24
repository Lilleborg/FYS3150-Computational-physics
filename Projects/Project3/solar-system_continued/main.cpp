#include <iostream>
#include <cmath>
#include <cstdlib>
#include "solarsystem.h"
#include "solver.h"
#include <string>
using namespace std;

int testing_main();
vec3 InitialCondition_CM(SolarSystem &solarSystem);

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

    // INITIAL CONDITIONS WHEN SUN IS HELD IN CENTER
    //solarSystem.createCelestialBody(vec3(-1.752200603881933E-01,9.675633320786794E-01,-3.799746898985921E-05),vec3(-1.720124877602163E-02,-3.130282140938300E-03,-2.538590515321615E-07)*365,3e-6,"Earth");
    //solarSystem.createCelestialBody(vec3(-4.261270488543623E+00,-3.367325372481964E+00, 1.093347180153562E-01),vec3(4.592148015424783E-03,-5.569898451309285E-03,-7.959975748130483E-05)*365,1.9/2*1e-3,"Jupiter");
    //solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");

    // INITIAL CONDITIONS WHEN CENTER IS CENTER OF MASS
    solarSystem.createCelestialBody( vec3(-1.734173457390217E-01,9.736937590796603E-01,-1.582107821713564E-04), vec3(-1.720709737865684E-02,-3.125258586509626E-03,-1.120932427483096E-07)*365, 3e-6, "Earth" );
    solarSystem.createCelestialBody( vec3(-4.259467773894452E+00,-3.361194945480983E+00,1.092145047021746E-01), vec3(4.586299412789570E-03,-5.564874896880609E-03,-7.945799167252124E-05)*365, 1.9/2*1e-3, "Jupiter");
    solarSystem.createCelestialBody(vec3(-1.581869997754351E+00,-3.828978953153063E-01, 3.059389984291728E-02), vec3(3.855008143708335E-03,-1.238923952632399E-02,-3.543305537962489E-04)*365, 3.3e-7, "Mars");
    solarSystem.createCelestialBody( vec3(-3.859054833019958E-01,-1.654307689835696E-03,3.481192038201179E-02), vec3(-5.294168138166344E-03,-2.691453995673129E-02,-1.714386730721826E-03)*356, 1.65e-7,"Mercury");
    solarSystem.createCelestialBody(vec3(7.293167005709342E-02,-7.175590811561052E-01,-1.415191215112003E-02), vec3(1.998700269409145E-02,1.911135291296663E-03,-1.127428703200971E-03)*365,2.45e-6,"Venus");
    solarSystem.createCelestialBody(vec3(1.772328745814774E+01,9.063002917185520E+00,-1.959478058581542E-01), vec3(-1.819603624325987E-03,3.318475309448707E-03,3.577108114482214E-05)*365,5.55e-5, "Uranus");
    solarSystem.createCelestialBody(vec3(2.868162693362844E+01,-8.591658348777845E+00,-4.840680053568654E-01), vec3(8.802822510921428E-04,3.025692572392946E-03,-8.295671458148408E-05)*365,1.03/2*1e-4, "Neptune");
    solarSystem.createCelestialBody(vec3(4.789734457676079E-02,-1.005701578936080E+01,1.729539849045261E-01), vec3(5.271615540953220E-03,8.862373325538410E-06,-2.100595333499852E-04)*365,5.5/2*1e-4, "Saturn");
    solarSystem.createCelestialBody(vec3(1.077826511187572E+01,-3.168642408143715E+01,2.729178542838963E-01), vec3(3.030812460422457E-03,3.426619083057393E-04,-9.199095031922107E-04)*365,1.31/2*1e-8, "Pluto");
    solarSystem.createCelestialBody(vec3(-2.452925329376519E+00,-7.723977367789784E-01,4.275617365061914E-01), vec3(2.640404541258229E-03,-1.059141794461857E-02,-8.215714583514224E-04)*365,9.393/2*1e-10, "Ceres");
    solarSystem.createCelestialBody(vec3(-2.039217469490588E+01,2.632421748180365E+01,-9.948727662866242E+00), vec3(1.551102962932346E-04,6.616059786287673E-04,-6.714831103374149E-05)*365,2.2/2*1e-16, "HalleysComet");
    solarSystem.createCelestialBody( vec3(0,0,0), InitialCondition_CM(solarSystem), 1.0, "Sun");
    cout << InitialCondition_CM(solarSystem) << endl;



    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of " <<body.name << " is " << body.position << " with velocity " << body.velocity << endl;
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


vec3 InitialCondition_CM(SolarSystem &solarSystem) //Calculates the initial velocity of the sun
{
    double sun_mass = 1.;
    vec3 init_vel;
    vector<CelestialBody> &bodies = solarSystem.bodies();
    for(int i=0; i<bodies.size(); i++) {
        init_vel += -1*(bodies[i].velocity*bodies[i].mass)/sun_mass;
    }
    return init_vel;
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
