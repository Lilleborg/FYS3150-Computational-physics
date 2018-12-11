#include <iostream>
#include "time.h"
#include <string.h>

#include "problem.h"
#include "montecarlo.h"
#include "writeme.h"
#include "population/a_seasons.h"
#include "population/a_constant.h"

using namespace std;

/* Brief code intro:
 * This main function use the class 'problem' to set up each problem we are looking at with different
 * parameters and timing.
 * A set of classes and common base classes are used. In the directory 'population' there are two
 * common bases 'population_group' and 'a_parameter'. a_constant' and 'a_seasons' is determined outside the 'problem'
 * and sendt in as a parameter just like the other parameters.
 *
 * The different population groups S, I and R shares common base 'population_group' and is initialized and handled
 * by the 'problem'.
 *
 * 'writeme' class is a work in progress for general c++ projects, intended to extend with more write functions.
 * Here it is used to write the different files we want to plot, it automaticly handles the different filenames and
 * directory paths set by the 'problem'.
 *
 * The RK4 solver was implemented first together with the 'problem' class, and is initialized and controlled by
 * the 'problem'. The MC solver was implemented last of all, at which point I didnt want to change too much in
 * 'problem'. In addition I think it's better that the 'solver' takes the problem as input, and not the other way around.
 * In hinsight I would like it if the RK4 solver operated in the same way as the MC solver.

*/
/* TODO:
 * comment throughout code
 * MPI? Set up own main.cpp for this? No need for MPI as the solvers are so fast.
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
    clock_t totstart = clock();

    if (numArguments == 2)  // cmd argument either A, B, C, D or E
    {
        if (strcmp(arguments[1],"A") == 0 || strcmp(arguments[1],"ALL") == 0)   // RUN EXERCISE A and B
        {
            problem A(400,300,100,"exeAandB/c_0.5_test");
            A.set_afunc(a_c);
            A.set_timing(0.1,10);
            for (double b = 1; b <= 1; b++)
            {
                // RK4
                A.set_parameters(b,c);
                A.set_population();
                A.evolve_full(debug);
                A.write_SIR_bin(write);

                // MC
//                A.set_population();
//                MonteCarlo MC_obj(&A,100);
//                MC_obj.Run_MC_const_population();
//                MC_obj.write_averages(write);
            }
            cout <<"A time end" << " " <<  A.time.back() << endl;

        }   // IF exe A AND B END

        if (strcmp(arguments[1],"C") == 0 || strcmp(arguments[1],"ALL") == 0)   // RUN EXERCISE C
        {
            problem C(400,300,100,"exeC/c_0.5_vary_dty");
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
            E.set_timing(0.0001,20);
            for (double b = 1; b <= 4; b++)
            {
                // RK4
                E.set_parameters(b,c,0,0,0,f);
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
    cout << "--------------\n";
    cout << "Main done in " << (double(clock()-totstart)/double(CLOCKS_PER_SEC)) << " seconds.\n" << endl;
    return 0;
}
