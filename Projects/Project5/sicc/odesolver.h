#ifndef ODESOLVER_H
#define ODESOLVER_H
#include "populations.h"
#include "vec3.h"

class ODEsolver
{
public:

    //u should be a function? how to do this hmm
    double m_dt;
    vec3 m_f;

    ODEsolver(double dt, vec3 f);
    void Euler();
    void RungeKutta4(class Populations &pop);
};

#endif // ODESOLVER_H
