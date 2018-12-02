#ifndef SUSCEPTIBLES_H
#define SUSCEPTIBLES_H

#include "population/a_parameter.h"

class Susceptibles
{
private:
    double m_c,m_d,m_e,m_f;
    int m_N,m_S0;
public:
    a_parameter *m_a_param;
    Susceptibles();
    Susceptibles(int N, int S0, a_parameter *a, double c, double d=0, double e=0, double f=0);
    ~Susceptibles();

    double S_n;
    double S_prime();

};


#endif // SUSCEPTIBLES_H
