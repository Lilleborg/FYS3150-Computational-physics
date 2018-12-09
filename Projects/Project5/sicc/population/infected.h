#ifndef INFECTED_H
#define INFECTED_H

#include "population/population_group.h"

using std::vector;


class Infected : public population_group
{
private:
    double m_b,m_d,m_dI;
    double m_N,m_I0;
    a_parameter *m_a_param;
    double current;
public:
    Infected();
    Infected(int N, int I0, a_parameter *a,double b, double d, double dI);
    ~Infected();

    double get_current();
    double prime(vector <double> Qs, double t);
    void add_to_current(double previous);

    // MC transitions
    double trans_I_R(double I, double dt){return m_b*I*dt;}
    double trans_I_D(double I, double dt){return m_d*I*dt;}
    double trans_I_DI(double I, double dt){return m_dI*I*dt;}
};
#endif // INFECTED_H
