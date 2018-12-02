#include "problem.h"

problem::problem(int N, int S0, int I0, int R0)
{
    m_N = N; m_S0 = S0; m_I0 = I0; m_R0 = R0;
}

problem::~problem()
{
    delete m_afunc;
    //delete m_S;
    //delete m_I;
    //delete m_R;
}

void problem::set_parameters(double a0,double b,double c,double d,double dI,double e,double f)
{
    m_a0 = a0; m_b = b; m_c = c; m_d = d; m_dI = dI; m_e = e; m_f = f;
}

void problem::set_population()
{
    m_S = new Susceptibles(m_N,m_S0,m_afunc,m_c,m_d,m_e,m_f);
    m_I = new Infected(m_N,m_I0,m_afunc,m_b,m_d,m_dI);
    m_R = new Recovered(m_N,m_R0,m_b,m_c,m_d,m_f);
    Quantities.push_back(m_S->S_n);
    Quantities.push_back(m_I->I_n);
    Quantities.push_back(m_R->R_n);
}
