#include <iostream>
#include "time.h"

#include "problem.h"
#include "writeme.h"
#include "population/a_seasons.h"
#include "population/a_constant.h"

using namespace std;

int main()
{
    // Constants
    double b = 2; double c = 0.5;

    // a-parameters
    a_constant *a_c = new a_constant(3);
    a_seasons *a_s = new a_seasons(4,1,M_PI);

    // writeme object
    writeme *write = new writeme("./../datafiles/");

    // Testing implementation
    bool debug = false;
    problem A(400,300,100,"exeA");
    A.set_afunc(a_s);
    A.set_parameters(b,c);
    A.set_population();
    A.set_timing(0.001,200);

    A.evolve_full(debug);
    //A.write_SIR_one_by_one(write);
    A.write_SIR(write);
    A.print_current_SIR(debug);




    // test writeme
    //    vector <vector<double>> testvec {{1,2,3},{4,5,6},{7,8,9}};
    //    cout << testvec.size() << endl;
    //    string path = "./../datafiles/";

    //    writeme writetest2(path, "test1");
    //    writetest2.add_double("a",4);
    //    writetest2.add_int("T",100);

    //    writetest2.write_vector_vector(testvec);

    cout << "Hello World!" << endl;
    return 0;
}
