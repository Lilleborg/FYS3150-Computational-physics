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
