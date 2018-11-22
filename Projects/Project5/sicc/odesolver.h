#ifndef ODESOLVER_H
#define ODESOLVER_H
#include "populations.h"
#include "vec3.h"

class ODEsolver
{
public:

    //u should be a function? how to do this hmm
    ODEsolver(double dt, vec3 u);
    void RungeKutta4(class Populations &pop);
};

#endif // ODESOLVER_H
