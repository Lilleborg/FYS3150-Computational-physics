#include "susceptibles.h"

Susceptibles::Susceptibles()
{
}

Susceptibles::~Susceptibles()
{
    delete m_a_param;
}

Susceptibles::Susceptibles(int N, int S0, a_parameter *a, double c, double d, double e, double f)
{
    m_N = N; m_S0 = S0;
    m_c = c; m_d = d; m_e = e; m_f = f;
    m_a_param = a;
    S_n = double(m_S0);
}

double Susceptibles::S_prime(vector <double> Qs, double t)
{
    return m_c*Qs[2]-m_a_param->a(t)*Qs[0]*Qs[1]/m_N-m_d*Qs[0]+m_e*m_N-m_f;
}

void Susceptibles::add_S_prime(vector <double> Qs, double t)
{
    this->S_n += this->S_prime(Qs,t);
}
