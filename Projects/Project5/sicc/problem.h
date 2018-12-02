#ifndef PROBLEM_H
#define PROBLEM_H

#include "population/a_parameter.h"
#include "population/susceptibles.h"
#include "population/infected.h"
#include "population/recovered.h"

//class a_parameter;

class problem
{
private:

public:
    problem(int N, int S0);
    ~problem();

    void set_parameters(double a0, double b, double c, double d=0, double e=0, double f=0); // init params
    void set_afunc(a_parameter *afunc){m_afunc = afunc;}    // sets the type of a parameter used
    void set_population();

    // Parameters
    a_parameter *m_afunc = nullptr; // pointer for parameter a class
    double m_a0,m_b,m_c,m_d,m_e,m_f;
    int m_N,m_S0,m_I0;    // initial conditions

    // Population groups
    Susceptibles *m_S = nullptr;
    Infected *m_I = nullptr;
    Recovered *m_R = nullptr;
};

#endif // PROBLEM_H
