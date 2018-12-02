#ifndef INFECTED_H
#define INFECTED_H

#include "population/a_parameter.h"
//#include "population/susceptibles.h"
#include "population/recovered.h"

class Infected
{
private:
    double m_c,m_d,m_e,m_f;
    int m_N,m_S0;
public:
    a_parameter *m_a_param;
    Infected();
    Infected(int N, int S0, a_parameter *a, double c, double d=0, double e=0, double f=0);
    ~Infected();

    double S_n;
    double S_prime();

};
#endif // INFECTED_H
