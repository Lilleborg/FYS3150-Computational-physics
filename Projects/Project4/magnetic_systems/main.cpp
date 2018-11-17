//#include <iostream>
#include "mpi.h"
#include "functions.h"
#include "exercises.h"
#include "time.h"

int main(int numArguments, char **arguments)
{
    int result = 0;
    cout << "suck my aaaaaaaaaaass" << endl;
    clock_t time_start = clock();
    int numprocs,my_rank;
    MPI_Init (&numArguments, &arguments);

    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    cout << "Hello world, I have  rank " << my_rank << " out of "
         << numprocs << endl;

    exe_d(1.0,"Up",1e4+5, numprocs, my_rank);

    /*
    if(numArguments > 2){  // If more than one cmd given = MPI, it reflects what exe to be run. Could be "ALL" to run all exes
        cout << "stuff is actually happening!" << endl;
        int MC_c = 60000;
        if (strcmp(arguments[4],"ALL") == 0){   // RUN ALL EXERCISES
            cout << "Running all exercises!\n";
            cout << "------------------------"<< endl;
            result += exe_b();

            result += exe_c(1.0,"Random",MC_c);
            result += exe_c(2.4,"Random",MC_c);
            result += exe_c(1.0,"Up",MC_c);
            result += exe_c(2.4,"Up",MC_c);

            result += exe_d(1.0,"Up",1e6);
        }
        if (strcmp(arguments[4],"B") == 0){   // RUN EXERCISE B
            result += exe_b();
        }
        if (strcmp(arguments[4],"C") == 0){   // RUN EXERCISE C
            int numprocs, my_rank;
            MPI_Init (&numArguments, &arguments);
            MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
            MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
            result += exe_c(1.0,"Random",MC_c);
            result += exe_c(2.4,"Random",MC_c);
            result += exe_c(1.0,"Up",MC_c);
            result += exe_c(2.4,"Up",MC_c);
            cout << "C!" << endl;
        }
        if (strcmp(arguments[4],"D") == 0){   // RUN EXERCISE D
            result += exe_d(1.0,"Up",1e6);
            result += exe_d(1.0,"Random",1e6);
            result += exe_d(2.4,"Up",1e6);
            result += exe_d(2.4,"Random",1e6);
        }
    }   // ONE CMD END
    if(numArguments == 2){  // If one cmd given = no MPI, it reflects what exe to be run. Could be "ALL" to run all exes

        int MC_c = 60000;
        if (strcmp(arguments[1],"ALL") == 0){   // RUN ALL EXERCISES
            cout << "Running all exercises!\n";
            cout << "------------------------"<< endl;
            result += exe_b();

            result += exe_c(1.0,"Random",MC_c);
            result += exe_c(2.4,"Random",MC_c);
            result += exe_c(1.0,"Up",MC_c);
            result += exe_c(2.4,"Up",MC_c);

            result += exe_d(1.0,"Up",1e6);
        }
        if (strcmp(arguments[1],"B") == 0){   // RUN EXERCISE B
            result += exe_b();
        }
        if (strcmp(arguments[1],"C") == 0){   // RUN EXERCISE C
            result += exe_c(1.0,"Random",MC_c);
            result += exe_c(2.4,"Random",MC_c);
            result += exe_c(1.0,"Up",MC_c);
            result += exe_c(2.4,"Up",MC_c);
        }
        if (strcmp(arguments[1],"D") == 0){   // RUN EXERCISE D
            result += exe_d(1.0,"Up",1e6);
            result += exe_d(1.0,"Random",1e6);
            result += exe_d(2.4,"Up",1e6);
            result += exe_d(2.4,"Random",1e6);
        }
    }   // ONE CMD END
*/
    //cout << "Main running for " << " " <<  double((clock()-time_start)/double(CLOCKS_PER_SEC)) << " seconds" << endl;
    MPI_Finalize ();
    return result;
} // MAIN END

