#include "recovered.h"

Recovered::Recovered()
{
}

Recovered::~Recovered()
{
}

Recovered::Recovered(int N,int R0,double b, double c, double d, double f)
{
    m_N = N; m_R0 = R0;
    m_b = b; m_c = c; m_d = d; m_f = f;

    current = double (m_R0);
}


double Recovered::prime(vector <double> Qs, double t)
{
    return m_b*Qs[1]-m_c*Qs[2]-m_d*Qs[2] + m_f;
}

void Recovered::add_to_current(double prev)
{
    current += prev;
}

double Recovered::get_current()
{
    return current;
}
