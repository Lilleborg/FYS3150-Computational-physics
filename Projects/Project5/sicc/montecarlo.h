#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "population/population_group.h"
#include <random>
//#include "population/recovered.h"
//#include "population/susceptibles.h"
//#include "population/infected.h"

#include "problem.h"
#include "writeme.h"

class MonteCarlo
{
private:
    double m_dt;
    problem *m_p = nullptr;
    int S,I,R,N,samples;
    vector<double> avgS, avgI, avgR;

    //Susceptibles *m_S = nullptr;
    //Infected *m_I = nullptr;
    //Recovered *m_R = nullptr;
public:
    MonteCarlo(problem *p, int samples);
    ~MonteCarlo(){}

    void find_dt(double N, double t);
    void Run_MC_const_population();

    void write_averages(writeme *write);

    double test(){cout << m_p->SIR[0]->trans_S_I(m_p->m_Qs[0],m_p->m_Qs[1],m_p->m_N,0,m_p->m_dt); return 0;}

};

#endif // MONTECARLO_H
