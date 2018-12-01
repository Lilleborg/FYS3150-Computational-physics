#include "a_seasons.h"

a_seasons::a_seasons(double a0_)
{
    m_a = a0_;
}

a_seasons::~a_seasons()
{
}

double a_seasons::a(double t)
{
    return A*cos(omega*t)+m_a;
}
