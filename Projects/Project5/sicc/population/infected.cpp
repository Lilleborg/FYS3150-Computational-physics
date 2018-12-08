#include "infected.h"

Infected::Infected()
{
}

Infected::~Infected()
{
}

Infected::Infected(int N, int I0, a_parameter *a, double b, double d, double dI)
{
    m_N = double(N); m_I0 = double(I0);
    m_b = b; m_d = d; m_dI = dI;
    m_a_param = a;
    current = double(m_I0);
}

double Infected::prime(vector <double> Qs, double t)
{
    return m_a_param->a(t)*Qs[0]*Qs[1]/m_N - m_b*Qs[1] - m_d*Qs[1] - m_dI*Qs[1];
}

void Infected::add_to_current(double prev)
{
    current += prev;
}

double Infected::get_current()
{
    return current;
}
