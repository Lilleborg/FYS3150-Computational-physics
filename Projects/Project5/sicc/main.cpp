#include <iostream>
#include "time.h"
#include <string.h>

#include "problem.h"
#include "montecarlo.h"
#include "writeme.h"
#include "population/a_seasons.h"
#include "population/a_constant.h"

using namespace std;

/* TODO:
 * comment throughout code
 * MPI? Set up own main.cpp for this?
 *
 *
 *
*/


int main(int numArguments, char **arguments)
{
    // a-parameters
    a_constant *a_c = new a_constant(4);
    a_seasons *a_s = new a_seasons(4,2,2.0*M_PI/5.0);
    // other parameters
    double c = 0.5;
    double d = 0.1;
    double dI = 0.5;
    double e = 0.3;
    double f = 0.2;

    // writeme object
    writeme *write = new writeme("./../datafiles/");


    bool debug = false;

    if (numArguments == 2)  // cmd argument either A, B, C, D or E
    {
        if (strcmp(arguments[1],"A") == 0 || strcmp(arguments[1],"ALL") == 0)   // RUN EXERCISE A and B
        {
            problem A(400,300,100,"exeAandB/c_0.5");
            A.set_afunc(a_c);
            A.set_timing(0.001,10);
            for (double b = 1; b <= 4; b++)
            {
                // RK4
                A.set_parameters(b,c);
                A.set_population();
                A.evolve_full(debug);
                A.write_SIR_bin(write);

                // MC
                A.set_population();
                MonteCarlo MC_obj(&A,100);
                MC_obj.Run_MC_const_population();
                MC_obj.write_averages(write);
            }

        }   // IF exe A AND B END

        if (strcmp(arguments[1],"C") == 0 || strcmp(arguments[1],"ALL") == 0)   // RUN EXERCISE C
        {
            problem C(400,300,100,"exeC/c_0.5");
            C.set_afunc(a_c);
            C.set_timing(0.001,40);
            for (double b = 1; b <= 4; b++)
            {
                // RK4
                C.set_parameters(b,c,d,dI,e);
                C.set_population();
                C.evolve_full(debug);
                C.write_SIR_bin(write);

                // MC
                C.set_population();
                MonteCarlo MC_obj(&C,100);
                MC_obj.Run_MC_extended();
                MC_obj.write_averages(write);
            }

        }   // IF exe C END

        if (strcmp(arguments[1],"D") == 0 || strcmp(arguments[1],"ALL") == 0)   // RUN EXERCISE D
            // TODO ADD MORE EXPERIEMENTAL PARAMETERS
        {
            problem D(400,300,100,"exeD/c_0.5");
            D.set_afunc(a_s);
            D.set_timing(0.001,40);
            for (double b = 1; b <= 4; b++)
            {
                // RK4
                D.set_parameters(b,c,d,dI,e);
                D.set_population();
                D.evolve_full(debug);
                D.write_SIR_bin(write);

                // MC
                D.set_population();
                MonteCarlo MC_obj(&D,100);
                MC_obj.Run_MC_extended();
                MC_obj.write_averages(write);
            }
        }   // IF exe D END

        if (strcmp(arguments[1],"E") == 0 || strcmp(arguments[1],"ALL") == 0)   // RUN EXERCISE E
            // TODO ADD MORE EXPERIEMENTAL PARAMETERS
        {
            problem E(400,300,100,"exeE/c_0.5");
            E.set_afunc(a_s);
            E.set_timing(0.001,40);
            for (double b = 1; b <= 4; b++)
            {
                // RK4
                E.set_parameters(b,c,d,dI,e,0.4);
                E.set_population();
                E.evolve_full(debug);
                E.write_SIR_bin(write);

                // MC
                E.set_population();
                MonteCarlo MC_obj(&E,100);
                MC_obj.Run_MC_extended();
                MC_obj.write_averages(write);
            }
        }   // IF exe E END
    }
    cout << "Main done!" << endl;
    return 0;
}
