#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <math.h>

#include "population/a_parameter.h"
#include "odesolver.h"
#include "population/population_group.h"
#include "population/susceptibles.h"
#include "population/infected.h"
#include "population/recovered.h"

// TODO: (?)
//vector <double> m_parameters; list of all parameters for printing current params for this problem
// add write to file functionality

class problem
{
public:
    // Initiallizers and setters
    problem(int N, int S0,int I0, int R0 = 0);
    ~problem();

    void set_parameters(double b, double c, double d=0, double dI=0, double e=0, double f=0);
    void set_timing(double dt, double T, double T0=0);
    void set_afunc(a_parameter *afunc){m_afunc = afunc;}
    void set_population();  // Initialize population classes

    // Parameters, initial conditions
    double m_b,m_c,m_d,m_dI,m_e,m_f;
    int m_N,m_S0,m_I0,m_R0;

    // Timestuff
    double m_dt,m_T,m_T0;
    int m_nr_steps;
    vector <double> time;

    // Vectors holding current SIR values
    vector <double> m_Qs = vector<double>(3,0);

    // Vectors holding all SIR values for writing
    vector <double> S_vector;
    vector <double> I_vector;
    vector <double> R_vector;

    // Population group objects in vector SIR, initialized by void set_population()
    vector <population_group*> SIR;

    // parameter a(t) object, set by void set_afunc() taking a_parameter object from outside
    a_parameter *m_afunc = nullptr;

    // ODEsolver object, initialized by void set_timing()
    ODEsolver *solver = nullptr;

    // Calculations
    void evolve();
    void update_current();

    // Convinient functions
    void print_current_SIR();
    vector <population_group*> get_SIR();
};

#endif // PROBLEM_H
