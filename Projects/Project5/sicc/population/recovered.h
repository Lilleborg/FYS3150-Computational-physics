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
    void add_to_current(double previous);

    // MC transitions
    double trans_R_S(double R, double dt){return m_c*R*dt;}
    double trans_R_D(double R, double dt){return m_d*R*dt;}
};

#endif // RECOVERED_H
