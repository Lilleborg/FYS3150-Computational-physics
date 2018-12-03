#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "problem.h"

class ODEsolver
{
public:

    double m_dt,k1,k2,k3,k4;
    vector <double> ks;

    ODEsolver(double dt);
    ~ODEsolver();

    // Integrators updating problem p 1 time step
    void Euler(problem *p);
    void get_ks();
    void RK4(problem *p);
};

#endif // ODESOLVER_H
