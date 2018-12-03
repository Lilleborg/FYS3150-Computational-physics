#ifndef SUSCEPTIBLES_H
#define SUSCEPTIBLES_H

#include "population/a_parameter.h"
#include <vector>

using std::vector;

class Susceptibles
{
private:
    double m_c,m_d,m_e,m_f;
    int m_N,m_S0;
public:
    a_parameter *m_a_param;
    Susceptibles();
    Susceptibles(int N, int S0, a_parameter *a, double c, double d, double e, double f);
    ~Susceptibles();

    double S_n;
    double S_prime(vector<double> Qs,double t);
    void add_S_prime(vector<double> Qs,double t);

};


#endif // SUSCEPTIBLES_H
