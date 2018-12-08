#include "montecarlo.h"
#include <iostream>

MonteCarlo::MonteCarlo(problem *p,int samples_)
{
    m_p = p;
    samples = samples_;
}

void MonteCarlo::find_dt(double N, double t)
{
    m_dt = 1;
    if (4/m_p->m_afunc->a(t)/N < m_dt) {m_dt = 4/m_p->m_afunc->a(t)/N;}
    if (1/m_p->m_b/N < m_dt) {m_dt = 1/m_p->m_b/N;}
    if (1/m_p->m_d/N < m_dt) {m_dt = 1/m_p->m_d/N;}
}

void MonteCarlo::Run_MC_const_population()
{
    mt19937 gen;
    uniform_real_distribution<double> RNG(0.0, 1.0);

    avgS = vector<double>(m_p->m_nr_steps,0);
    avgI = vector<double>(m_p->m_nr_steps,0);
    avgR = vector<double>(m_p->m_nr_steps,0);

    for (int cycle = 0; cycle < samples; ++cycle) {

        S = m_p->m_S0; I = m_p->m_I0; R = m_p->m_R0; N = m_p->m_N;

        for (u_long i = 0; i < m_p->m_nr_steps; ++i) {
            find_dt(N,m_p->time[i]);

            avgS[i] += S/double(samples);
            avgI[i] += I/double(samples);
            avgR[i] += R/double(samples);

            if (RNG(gen) < m_p->SIR[0]->trans_S_I(S,I,N,m_p->time[i],m_dt)){S -= 1; I += 1;}
            if (RNG(gen) < m_p->SIR[1]->trans_I_R(I,m_dt)){I -= 1; R += 1;}
            if (RNG(gen) < m_p->SIR[2]->trans_R_S(R,m_dt)){R -= 1; S += 1;}


        }
    }
}

void MonteCarlo::write_averages(writeme *write)
{
    m_p->config_write(write,"SIR_MC");
    vector<vector<double>> temp;
    temp.push_back(avgS);
    temp.push_back(avgI);
    temp.push_back(avgR);
    write->write_vector_vector_bin(temp);
}
