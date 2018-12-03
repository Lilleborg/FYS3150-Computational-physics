#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>

#include "population/a_parameter.h"
#include "population/susceptibles.h"
#include "population/infected.h"
#include "population/recovered.h"

//class a_parameter;
//vector <double> m_parameters; TODO?: list of all parameters for printing current params for this problem

class problem
{
private:

public:
    // Initiallizers and setters
    problem(int N, int S0,int I0, int R0 = 0);
    ~problem();
    void set_parameters(double b, double c, double d=0, double dI=0, double e=0, double f=0); // init params
    void set_afunc(a_parameter *afunc){m_afunc = afunc;}    // sets a parameter class to be used
    void set_population();  // Initialize/(reset to current params) population classes

    // Parameters, initial conditions
    double m_b,m_c,m_d,m_dI,m_e,m_f;
    int m_N,m_S0,m_I0,m_R0;    // initial conditions

    // Vectors holding SIT values
    //vector <double> m_Qs = {m_S->S_n,m_I->I_n,m_R->R_n}; // Current SIR values
    vector <double> m_Qs = {0,0,0}; // Current SIR values
    // Vectors holding all SIR values for writing
    vector <double> S_vector;
    vector <double> I_vector;
    vector <double> R_vector;

    // Population group classes, initialized by void set_population()
    Susceptibles *m_S = nullptr;
    Infected *m_I = nullptr;
    Recovered *m_R = nullptr;
    // parameter a(t) class, set by void set_afunc() taking a_parameter object from outside
    a_parameter *m_afunc = nullptr;

    // Calculations
    void evolve();
    void update_current();

    // Convinient functions
    void print_current_SIR();


};

#endif // PROBLEM_H
