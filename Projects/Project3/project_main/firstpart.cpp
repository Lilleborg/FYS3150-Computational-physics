#include "firstpart.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

// Declare functions



int main(int argc, char *argv[]){
    int n;  // number of points
    double end_time; //end time for simulation in [yr]
    string filename;

    // command line arguments
    if (argc <= 3){
        cout << "--- Please give commands: Output base filename, Number of integration points, End time FIX THIS ---" << endl;
        // Base Filename used in all outputfiles in begining of name
        // Number of integration points not included initial condition, such that arrays have length N+1
        // End time used to calculate step length
        // MAYBE CHANGE THIS SO THAT USER GIVES STEP LENGTH?

    }
    else {
        filename = argv[1]; n = atoi(argv[2]); end_time = atof(argv[3]);
    }

    //TESTING
    if (argc == 6){
        cout << "--- TESTING OPTION STARTED; if argv[3] == 1, only tests will be ran, FIX THIS ---" << endl;
        int testing = atoi(argv[3]);
        // Tests:

        // Option for exiting:
        if (testing == 1){
            exit(1);
        }
    }

    // initializing
    double h = end_time/n;  // stepsize
    double *x = new double [n+1]; double *y = new double [n+1]; double *z = new double [n+1];

    cout << "hei" << endl;
}

void forward_euler_3D(double *x){
    x = x;
}

