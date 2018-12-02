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

    R_n = double (m_R0);
}
