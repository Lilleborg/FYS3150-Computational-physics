#include "susceptibles.h"

Susceptibles::Susceptibles()
{

}

Susceptibles::Susceptibles(int N, int S0, a_parameter *a, double c, double d, double e, double f)
{
    m_N = N; m_S0 = S0;
    m_c = c; m_d = d; m_e = e; m_f = f;
    m_a_param = a;
    S_n = double(m_S0);
}

Susceptibles::~Susceptibles()
{
    delete m_a_param;
}
