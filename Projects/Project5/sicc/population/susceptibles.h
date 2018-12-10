#ifndef SUSCEPTIBLES_H
#define SUSCEPTIBLES_H

#include "population/population_group.h"
#include "iostream"

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

    // MC transitions
    double trans_S_I(double S, double I,double N, double t, double dt){return m_a_param->a(t)*S*I*dt/N;}
    double trans_S_R(double dt){return m_f*dt;} // std::cout << m_f*dt << " " << "in S to R" << std::endl;
    double trans_S_D(double S, double dt){return m_d*S*dt;}
    double trans_E_S(double N, double dt){return m_e*N*dt;}

};


#endif // SUSCEPTIBLES_H
