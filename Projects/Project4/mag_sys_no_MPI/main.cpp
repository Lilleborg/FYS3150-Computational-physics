//#include <iostream>
#include "functions.h"
#include "exercises.h"
#include "time.h"

int main(int numArguments, char **arguments)
{
    int result = 0;
    cout << "main" << endl;
    clock_t time_start = clock();

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
    cout << "Main running for " << " " <<  double((clock()-time_start)/double(CLOCKS_PER_SEC)) << " seconds" << endl;
    return result;
} // MAIN END

