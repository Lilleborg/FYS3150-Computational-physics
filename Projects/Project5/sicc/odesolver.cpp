#include "odesolver.h"

ODEsolver::ODEsolver(double dt, vec3 f) :
    m_dt(dt), m_f(f)
{   

}

//u' = f(t,u). f should then be right hand side of ODE. How to deal with this with coupled differential equations? :( vec3?
   //create seperate .cpp-file that contains S', I', R'.

void ODEsolver::Euler(){


}


/*
void ODEsolver::RungeKutta4(class Populations &pop){
    //LOOP OVER POPULATIONS
    for(){
        //for each population ABCD, calculate the vec3 u = S,I,R
        double k1 = m_dt*f(pop.u )
        pop.u += 1./6*(k1+2*k2+2*k3+k4)*dt
        //FINISH RUNGE KUTTA 4. How to deal with function and half indices?


    }
}
*/