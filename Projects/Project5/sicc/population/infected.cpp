#include "infected.h"

Infected::Infected()
{

}

Infected::~Infected()
{
    delete m_a_param;
}

Infected::Infected(int N, int I0, a_parameter *a, double b, double d, double dI)
{
    m_N = N; m_I0 = I0;
    m_b = b; m_d = d; m_dI = dI;
    m_a_param = a;
    I_n = double(m_I0);
}

double Infected::I_prime(vector <double> Qs, double t)
{
    return m_a_param->a(t)*Qs[0]*Qs[1]/m_N - m_b*Qs[1] - m_d*Qs[1] - m_dI*Qs[1];
}

void Infected::add_I_prime(vector <double> Qs, double t)
{
    this->I_n += this->I_prime(Qs,t);
}

