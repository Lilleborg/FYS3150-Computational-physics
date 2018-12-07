#include <iostream>
#include "time.h"

#include "problem.h"
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
    a_seasons *a_s = new a_seasons(4,2,1/2.0*M_PI);

    // writeme object
    writeme *write = new writeme("./../datafiles/");

    // Exercise A
    bool debug = true;
    double c = 0.5;
    problem A(400,300,100,"exeA/c_0.5");
    A.set_afunc(a_c);
    A.set_timing(0.001,20);
    for (double b = 1; b <= 1; b++)
    {
        A.set_parameters(b,c);
        A.set_population();
        A.evolve_full(debug);
        A.write_SIR_bin(write);
    }



    cout << "Main done!" << endl;
    return 0;
}
