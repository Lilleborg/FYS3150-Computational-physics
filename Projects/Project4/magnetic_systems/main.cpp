//#include <iostream>
#include "functions.h"
#include "exercises.h"

int main(int numArguments, char **arguments)
{
    int MC = 60000;      // # cycles

    //exe_b();
    exe_c(1.0,"Random",MC);
    exe_c(2.4,"Random",MC);
    exe_c(1.0,"Up",MC);
    exe_c(2.4,"Up",MC);

    return 0;
} // MAIN END

