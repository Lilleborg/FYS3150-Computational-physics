#ifndef A_SEASONS_H
#define A_SEASONS_H

#include "population/a_parameter.h"
#include <math.h>

class a_seasons : public a_parameter
{
private:
    double m_a,m_A,m_omega;
public:
    a_seasons(double a0, double A, double omega);
    ~a_seasons();

    double a(double t);
};

#endif // A_SEASONS_H
