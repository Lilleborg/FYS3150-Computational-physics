#include <iostream>
#include <math.h>
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
    a_constant a_c(3);
    a_seasons *a_s = new a_seasons(4,1,M_PI);

    // Oppgave A
    problem A(400,300,100);
    A.set_parameters(b,c);
    A.set_afunc(a_s);
    A.set_population();
    A.m_b = 2;
    A.set_population();
    cout << a_c.a(2) << " " << a_s->a(1.0/2) << " " << A.m_S->m_a_param->a(1.0/2) << endl;
    //cout << A.m_I->m_b << endl; testing
    for (auto &Qs : A.Quantities)
    {
        cout << Qs << endl;
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
