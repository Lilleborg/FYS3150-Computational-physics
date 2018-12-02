#include "problem.h"

problem::problem(int N, int S0)
{
    m_N = N; m_S0 = S0; m_I0 = N-S0;
}

problem::~problem()
{
    delete m_afunc;
    delete m_S;
    delete m_I;
    delete m_R;
}

void problem::set_parameters(double a0,double b,double c,double d,double e,double f)
{
    m_a0 = a0; m_b = b; m_c = c; m_d = d; m_e = e; m_f = f;
}

void problem::set_population()
{
    m_S = new Susceptibles(m_N,m_S0,m_afunc,m_c,m_d,m_e,m_f);
}
