#include <iostream>
#include "time.h"

#include "problem.h"
#include "montecarlo.h"
#include "writeme.h"
#include "population/a_seasons.h"
#include "population/a_constant.h"

using namespace std;

/* TODO:
 * Add monte carlo solver
 * MPI? Set up own main.cpp for this?
 *
 *
 *
*/


int main()
{
    // a-parameters
    a_constant *a_c = new a_constant(4);
    a_seasons *a_s = new a_seasons(4,2,2.0*M_PI/5.0);

    // writeme object
    writeme *write = new writeme("./../datafiles/");

    // Exercise A
    bool debug = false;
    double c = 0.5;
    problem A(400,300,100,"exeA/c_0.5/d_0.1");
    A.set_afunc(a_c);
    A.set_timing(0.001,20);
    for (double b = 1; b <= 4; b++)
    {
        A.set_parameters(b,c,0.1,0.,0,0);
        A.set_population();
        A.print_current_SIR();
        A.evolve_full(debug);
        A.write_SIR_bin(write);
        //A.write_SIR(write);
    }



    // MC testing
    problem *AMC = new problem(400,300,100,"exeA/c_0.5/d_0.1");
    AMC->set_afunc(a_c);
    AMC->set_timing(0.001,20);

    for (double b = 1; b <= 4; b++)
    {
        AMC->set_parameters(b,c,0.1,0,0,0);
        AMC->set_population();
        MonteCarlo MC_obj(AMC,100);
        MC_obj.Run_MC_extended(write);
        MC_obj.write_averages(write);
    }


    cout << "Main done!" << endl;
    return 0;
}
