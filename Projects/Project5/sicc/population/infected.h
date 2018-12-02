#ifndef INFECTED_H
#define INFECTED_H

#include "population/a_parameter.h"
#include <vector>

using std::vector;


class Infected
{
private:
    double m_d,m_dI;
    int m_N,m_I0;
    a_parameter *m_a_param;
public:
    Infected();
    Infected(int N, int I0, a_parameter *a,double b, double d, double dI);
    ~Infected();

    double I_n,m_b;
    double I_prime();

};
#endif // INFECTED_H
