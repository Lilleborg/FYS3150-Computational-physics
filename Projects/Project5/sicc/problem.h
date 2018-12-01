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
    problem(int N_, int S0_, int I0_);
    ~problem();

    void set_parameters(double a0_,double b_,double c_,double d_=0,double e_=0,double f_=0); // init params
    void set_afunc(a_parameter *afunc){m_afunc = afunc;}    // sets the type of a parameter used
    void set_population();

    // Parameters
    a_parameter *m_afunc = nullptr; // pointer for parameter a class
    double a0,b,c,d,e,f;
    int N,S0,I0;    // initial conditions

    // Population groups
    Susceptibles S;
    Infected I;
    Recovered R;
};

#endif // PROBLEM_H
