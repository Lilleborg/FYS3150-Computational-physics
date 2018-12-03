#include <iostream>

//#include "populations.h"

#include "problem.h"
#include "population/a_seasons.h"
#include "population/a_constant.h"

using namespace std;

int main()
{
    // Constants
    double b = 1; double c = 0.5;

    // a-parameters
    a_constant *a_c = new a_constant(3);
    a_seasons *a_s = new a_seasons(4,1,M_PI);

    // Oppgave A
//    problem A(400,300,100);
//    A.set_parameters(b,c);
//    A.set_afunc(a_s);
//    A.set_population();
//    A.m_b = 2;
//    A.set_population();
//    cout << a_c->a(2) << " " << a_s->a(1.0/2) << " " << endl; // << A.SIR[0]->m_a_param->a(1.0/2)
//    //cout << A.m_I->m_b << endl; testing
//    for (auto &Qs : A.m_Qs)
//    {
//        cout << Qs << endl;
//    }

    // Testing implementation
    cout << "Testing stuff\n" << endl;
    problem test(400,300,100);
    test.set_afunc(a_c);
    test.set_parameters(b,c);
    test.set_population();
    test.set_timing(0.01,2);

    test.print_current_SIR();
    for (int var = 0; var < 5; ++var) {
        test.evolve();
        test.print_current_SIR();
    }






    // Initialize populations
//    vector<double> as = {4,4,4,4};
//    vector<double> bs = {1,2,3,4};
//    vector<double> cs = {0.5,0.5,0.5,0.5};
//    vector<Populations> m_populations;
//    for (int i = 0; i < 4; ++i) {
//        m_populations
//    }
//    Popa = Populations()






    cout << "Hello World!" << endl;
    return 0;
}
