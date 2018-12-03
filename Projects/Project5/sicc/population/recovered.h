#ifndef RECOVERED_H
#define RECOVERED_H

#include "population/population_group.h"

using std::vector;

class Recovered : public population_group
{
private:
    double m_b,m_c,m_d,m_f;
    int m_N,m_R0;
    double current;
public:
    Recovered();
    Recovered(int N,int R0,double b, double c, double d, double f);
    ~Recovered();

    double get_current();
    double prime(vector <double> Qs, double t);
    void add_prime(vector <double> Qs, double t);
};

#endif // RECOVERED_H
