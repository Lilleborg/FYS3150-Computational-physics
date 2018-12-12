#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "population/population_group.h"
#include "time.h"

class problem;

// TODO: add lists of values to add in get_ks() for looping
class ODEsolver
{
private:
    // experiment: try to overload operator on std::vector object?
    //    friend std::vector<double> &operator+(vector<double> &os, const vec3& myVector);
    //    std::vector<double> &operator+(vector<double> *this,vector <double> &vec,double &plussing);
public:

    double m_dt;
    vector <double> ks;// = vector <double> (4,0);
    vector<double> k_S;
    vector<double> k_I;
    vector<double> k_R;

    problem *m_problem;

    ODEsolver(problem *p_, double dt);
    ~ODEsolver();

    // Convenient
    void get_ks(population_group *p, double t);
    vector<double> vec_pluss(const vector<double> vec,double pluss);
    vector<double> vec_pluss(const vector<double> vec, double x, double y, double z);   // use instead!

    // Integrators updating problem m_problem 1 time step
    //void Euler(population_group *p);  // see how bad euler handles the problem?

    void RK4(population_group *p, double t);
    void RK4(vector<population_group*> SIR,double t);
};

#endif // ODESOLVER_H
