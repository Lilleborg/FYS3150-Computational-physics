#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <random>

#include "population/population_group.h"
#include "problem.h"
#include "writeme.h"


class MonteCarlo
{
private:
    double m_dt,avg_sigS, avg_sigI, avg_sigR;
    problem *m_p = nullptr;
    int S,I,R,N,samples;
    vector<double> avgS, avgI, avgR, varS, varI, varR, time, MC_time;
public:
    MonteCarlo(problem *p, int samples);
    ~MonteCarlo(){}

    void find_dt(double N, double t);
    void find_dt_extended(double N, double t);

    void Run_MC_const_population();
    void Run_MC_extended();

    // Write to file funcs
    void write_averages(writeme *write);
    void write_SIR_vectors(writeme *write);


};

#endif // MONTECARLO_H
