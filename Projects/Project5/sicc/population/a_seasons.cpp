#include "a_seasons.h"

a_seasons::a_seasons(double a0, double A, double omega)
{
    m_a = a0; m_A = A; m_omega = omega;
}

a_seasons::~a_seasons()
{
}

double a_seasons::a(double t)
{
    return m_A*cos(m_omega*t)+m_a;
}
