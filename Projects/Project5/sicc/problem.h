#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "time.h"

#include "population/a_parameter.h"
#include "writeme.h"
#include "odesolver.h"
#include "population/population_group.h"
#include "population/susceptibles.h"
#include "population/infected.h"
#include "population/recovered.h"

using namespace std;

// TODO: (?)
//printing current params for this problem

class problem
{
public:
    // Initiallizers and setters
    problem(int N, int S0,int I0,string name_ = "", int R0 = 0);
    ~problem();

    void set_parameters(double b, double c, double d=0, double dI=0, double e=0, double f=0);//init param
    void set_timing(double dt, double T, double T0=0);  // init timing and ODEsolver
    void set_afunc(a_parameter *afunc){m_afunc = afunc;}    // init a parameter
    void set_population();  // Initialize population classes

    // Calculations
    void evolve(double t);  // evolve SIR systems 1 step
    void evolve(int i); // evolve using index
    void update_current();  // update local current values of current SIR
    void evolve_full(bool debug = false); // run full simulation untill time[i] = T, with test of total population if test = true
    void update_all();  // add current values to SIR vectors
    void update_all(double S, double I, double R);  // add values S I R to SIR vectors
    bool test_total_population(); double test_sum;

    // Convinient functions
    void print_current_SIR(bool debug = false);
    vector <population_group*> get_SIR();

    // Parameters, initial conditions
    string name;
    double m_b,m_c,m_d,m_dI,m_e,m_f;
    map <string,double> m_params;
    int m_N,m_S0,m_I0,m_R0;

    // Timestuff
    double m_dt,m_T,m_T0;
    int m_nr_steps,current_step;
    vector <double> time;

    // Vectors holding current SIR values
    vector <double> m_Qs = vector<double>(3,0);
    vector <double> S_vector;
    vector <double> I_vector;
    vector <double> R_vector;

    // Population group objects in vector SIR, initialized by void set_population()
    vector <population_group*> SIR;

    // parameter a(t) object, set by void set_afunc() taking a_parameter object from outside
    a_parameter *m_afunc = nullptr;

    // ODEsolver object, initialized by void set_timing()
    ODEsolver *solver = nullptr;

    // Writing to file
    void config_write(writeme *write, string filenamestart = "SIR");
    void write_SIR(writeme *write, bool config = true);
    void write_SIR_bin(writeme *write, bool config = true);
    void write_SIR_one_by_one(writeme *write, bool config = true);

};

#endif // PROBLEM_H
