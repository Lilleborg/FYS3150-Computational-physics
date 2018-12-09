#include "montecarlo.h"

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
    if (1/m_p->m_c/N < m_dt) {m_dt = 1/m_p->m_c/N;}
}

void MonteCarlo::find_dt_extended(double N, double t)
{
    find_dt(N,t);
    if (1/m_p->m_d/N < m_dt) {m_dt = 1/m_p->m_d/N;}

    if (1/(m_p->m_dI)/N < m_dt) {m_dt = 1/(m_p->m_dI)/N ;}

    if (1/m_p->m_e/N < m_dt) {m_dt = 1/m_p->m_e/N;}

    if (1/m_p->m_f < m_dt) {m_dt = 1/m_p->m_f;}
}

//if (m_p->m_f != 0)
//{
//}
void MonteCarlo::Run_MC_const_population()
{
    mt19937 gen;
    uniform_real_distribution<double> RNG(0.0, 1.0);

    avgS = vector<double>(m_p->m_nr_steps,0);
    avgI = vector<double>(m_p->m_nr_steps,0);
    avgR = vector<double>(m_p->m_nr_steps,0);

    cout << "Running MC const of problem " << m_p->name << " with " << m_p->m_nr_steps << " steps\n";
    cout << "..." << endl;
    clock_t timestart = clock();
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
    cout << "MC done in " << (double(clock()-timestart)/double(CLOCKS_PER_SEC)) << " seconds.\n" << endl;
}

void MonteCarlo::Run_MC_extended(writeme *write)
{
    mt19937 gen;
    uniform_real_distribution<double> RNG(0.0, 1.0);
    vector<population_group*> SIR = m_p->get_SIR();
    //vector<double> Qs = m_p

    avgS = vector<double>(m_p->m_nr_steps,0);
    avgI = vector<double>(m_p->m_nr_steps,0);
    avgR = vector<double>(m_p->m_nr_steps,0);

    cout << "Running MC extended of problem " << m_p->name << " with " << m_p->m_nr_steps << " steps\n";
    cout << "..." << endl;
    clock_t timestart = clock();
    for (int cycle = 0; cycle < samples; ++cycle) {

        S = m_p->m_S0; I = m_p->m_I0; R = m_p->m_R0; N = m_p->m_N;
        time = m_p->time;

        for (u_long i = 0; i < m_p->m_nr_steps; ++i) {
            find_dt_extended(N,time[i]);

            // Calculate averages for this time step
            avgS[i] += S/double(samples);
            avgI[i] += I/double(samples);
            avgR[i] += R/double(samples);

            // Accept or reject transitions, set up SIR values for next time step
            // Out of S:
            if (RNG(gen) < SIR[0]->trans_S_I(S,I,N,time[i],m_dt)) {S -= 1; I += 1;}
            if (RNG(gen) < SIR[0]->trans_S_R(m_dt)) {S -= 1; R += 1;}
            if (RNG(gen) < SIR[0]->trans_S_D(S,m_dt)) {S -= 1;}

            // Out of I:
            if (RNG(gen) < SIR[1]->trans_I_R(I,m_dt)) {I -= 1; R += 1;}
            if (RNG(gen) < SIR[1]->trans_I_D(I,m_dt)) {I -= 1;}
            if (RNG(gen) < SIR[1]->trans_I_DI(I,m_dt)) {I -= 1;}

            // Out of R:
            if (RNG(gen) < SIR[2]->trans_R_S(R,m_dt)) {R -= 1; S += 1;}
            if (RNG(gen) < SIR[2]->trans_R_D(R,m_dt)) {R -=1;}


            //m_p->update_all(S,I,R);
            //m_p->write_SIR_bin(write,false);
        }
    }
    cout << "MC done in " << (double(clock()-timestart)/double(CLOCKS_PER_SEC)) << " seconds.\n" << endl;
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

void MonteCarlo::write_SIR_vectors(writeme *write)
{
    m_p->config_write(write,"SIR_MC");
    m_p->write_SIR_bin(write,false);
}
