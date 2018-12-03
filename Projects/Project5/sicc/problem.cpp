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

void problem::set_parameters(double b, double c, double d, double dI, double e, double f)
{
    m_b = b; m_c = c; m_d = d; m_dI = dI; m_e = e; m_f = f;
}

void problem::set_population()
{
    m_S = new Susceptibles(m_N,m_S0,m_afunc,m_c,m_d,m_e,m_f);
    m_I = new Infected(m_N,m_I0,m_afunc,m_b,m_d,m_dI);
    m_R = new Recovered(m_N,m_R0,m_b,m_c,m_d,m_f);
    m_Qs[0] = m_S->S_n;
    m_Qs[1] = m_I->I_n;
    m_Qs[2] = m_R->R_n;
}

void problem::update_current()
{
    m_Qs[0] = m_S->S_n;
    m_Qs[1] = m_I->I_n;
    m_Qs[2] = m_R->R_n;
}

void problem::evolve()
{
    m_S->add_S_prime(m_Qs,1);
    update_current();
}

void problem::print_current_SIR()
{
   std::cout << "S: " << m_Qs[0] << " , I: " << m_Qs[1] << " , R: " << m_Qs[2] << std::endl;
}
