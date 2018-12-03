#ifndef SUSCEPTIBLES_H
#define SUSCEPTIBLES_H

#include "population/population_group.h"

using std::vector;

class Susceptibles : public population_group
{
private:
    double m_c,m_d,m_e,m_f;
    int m_N,m_S0;
    double current;
    a_parameter *m_a_param;
public:
    Susceptibles();
    Susceptibles(int N, int S0, a_parameter *a, double c, double d, double e, double f);
    ~Susceptibles();

    double get_current();
    double prime(vector<double> Qs, double t);
    void add_to_current(double previous);

};


#endif // SUSCEPTIBLES_H
