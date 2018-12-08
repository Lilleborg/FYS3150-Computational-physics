#ifndef POPULATION_GROUP_H
#define POPULATION_GROUP_H

#include "population/a_parameter.h"
#include <vector>

using std::vector;

class population_group
{
public:
    population_group();
    virtual ~population_group();

    virtual double get_current() = 0;
    virtual double prime(vector <double> Qs, double t) = 0;
    virtual void add_to_current(double previous) = 0;

    // MC Transition probabilities (This might be done more elegantly!)
    // transitions for S
    virtual double trans_S_I(double S, double I,double N, double t, double dt){}
    virtual double trans_S_R(double dt){}
    virtual double trans_S_D(double S, double dt){}
    virtual double trans_E_S(double N, double dt){}

    // transitions for I
    virtual double trans_I_R(double I, double dt){}
    virtual double trans_I_D(double I, double dt){}

    // transitions for R
    virtual double trans_R_S(double R, double dt){}
    virtual double trans_R_D(double R, double dt){}
};

#endif // POPULATION_GROUP_H
