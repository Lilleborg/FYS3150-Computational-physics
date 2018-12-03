#ifndef INFECTED_H
#define INFECTED_H

#include "population/population_group.h"

using std::vector;


class Infected : public population_group
{
private:
    double m_b,m_d,m_dI;
    int m_N,m_I0;
    a_parameter *m_a_param;
    double current;
public:
    Infected();
    Infected(int N, int I0, a_parameter *a,double b, double d, double dI);
    ~Infected();

    double get_current();
    double prime(vector <double> Qs, double t);
    void add_prime(vector <double> Qs, double t);

};
#endif // INFECTED_H
