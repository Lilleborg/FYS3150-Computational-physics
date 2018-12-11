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
    // Here we don't check if a parameter is zero, as if example f=0 then
    // 1/m_p->m_f = inf wich is not < m_dt. This saves a lot of if tests
    find_dt(N,t);

    if (1/m_p->m_d/N < m_dt) {m_dt = 1/m_p->m_d/N;}

    if (1/(m_p->m_dI)/N < m_dt) {m_dt = 1/(m_p->m_dI)/N ;}

    if (1/m_p->m_e/N < m_dt) {m_dt = 1/m_p->m_e/N;}

    if (1/m_p->m_f < m_dt) {m_dt = 1/m_p->m_f;}

}

void MonteCarlo::Run_MC_const_population()
{
    mt19937 gen;
    uniform_real_distribution<double> RNG(0.0, 1.0);

    avgS = vector<double>(m_p->m_nr_steps,0);
    avgI = vector<double>(m_p->m_nr_steps,0);
    avgR = vector<double>(m_p->m_nr_steps,0);

    varS = vector<double>(m_p->m_nr_steps,0);
    varI = vector<double>(m_p->m_nr_steps,0);
    varR = vector<double>(m_p->m_nr_steps,0);

    avg_sigS = 0;
    avg_sigI = 0;
    avg_sigR = 0;

    cout << "Running MC const of problem " << m_p->name << " with " << m_p->m_nr_steps << " steps\n";
    cout << "..." << endl;
    clock_t timestart = clock();
    for (int cycle = 0; cycle < samples; ++cycle) {

        S = m_p->m_S0; I = m_p->m_I0; R = m_p->m_R0; N = m_p->m_N;
        time = m_p->time;
        u_long nr_steps = m_p->m_nr_steps;
        vector<double> MC_time;

        for (u_long i = 0; i < nr_steps; ++i) {
            //find_dt(N,time[i]);
            m_dt = 0.001;
            MC_time.push_back(i*m_dt);

            avgS[i] += S/double(samples);
            avgI[i] += I/double(samples);
            avgR[i] += R/double(samples);

            if (time[i] > 5)
            {
                varS[i] += (avgS[i]-S)*(avgS[i]-S)/(samples-1);
                varI[i] += (avgI[i]-I)*(avgI[i]-I)/(samples-1);
                varR[i] += (avgR[i]-R)*(avgR[i]-R)/(samples-1);

                avg_sigS += sqrt(varS[i])/(samples*nr_steps);
                avg_sigI += sqrt(varI[i])/(samples*nr_steps);
                avg_sigR += sqrt(varR[i])/(samples*nr_steps);
            }
            if (RNG(gen) < m_p->SIR[0]->trans_S_I(S,I,N,time[i],m_dt)){S -= 1; I += 1;}
            if (RNG(gen) < m_p->SIR[1]->trans_I_R(I,m_dt)){I -= 1; R += 1;}
            if (RNG(gen) < m_p->SIR[2]->trans_R_S(R,m_dt)){R -= 1; S += 1;}
        }
        cout << MC_time.back() << endl;
    }
    cout << "MC done in " << (double(clock()-timestart)/double(CLOCKS_PER_SEC)) << " seconds.\n" << endl;
}

void MonteCarlo::Run_MC_extended()
{
    // Using this for exe C and onwards, not checking of d = 0 or e = 0 as this is unrealistic
    mt19937 gen;
    uniform_real_distribution<double> RNG(0.0, 1.0);
    vector<population_group*> SIR = m_p->get_SIR();

    avgS = vector<double>(m_p->m_nr_steps,0);
    avgI = vector<double>(m_p->m_nr_steps,0);
    avgR = vector<double>(m_p->m_nr_steps,0);

    varS = vector<double>(m_p->m_nr_steps,0);
    varI = vector<double>(m_p->m_nr_steps,0);
    varR = vector<double>(m_p->m_nr_steps,0);

    avg_sigS = 0;
    avg_sigI = 0;
    avg_sigR = 0;

    cout << "Running MC extended of problem " << m_p->name << " with " << m_p->m_nr_steps << " steps\n";
    cout << "..." << endl;
    clock_t timestart = clock();
    for (int cycle = 0; cycle < samples; ++cycle) {

        S = m_p->m_S0; I = m_p->m_I0; R = m_p->m_R0; N = m_p->m_N;
        time = m_p->time;
        u_long nr_steps = m_p->m_nr_steps;
        vector<double> MC_time;

        for (u_long i = 0; i < nr_steps; ++i) {
            find_dt_extended(N,time[i]);
            //m_dt = m_p->m_dt;
            MC_time.push_back(m_dt);

            // Calculate averages variance and avg standard deviation
            avgS[i] += S/double(samples);
            avgI[i] += I/double(samples);
            avgR[i] += R/double(samples);

            if (time[i]>5)
            {
                varS[i] += (avgS[i]-S)*(avgS[i]-S)/(samples-1);
                varI[i] += (avgI[i]-I)*(avgI[i]-I)/(samples-1);
                varR[i] += (avgR[i]-R)*(avgR[i]-R)/(samples-1);

                avg_sigS += sqrt(varS[i])/(samples*nr_steps);
                avg_sigI += sqrt(varI[i])/(samples*nr_steps);
                avg_sigR += sqrt(varR[i])/(samples*nr_steps);
            }

            // Accept or reject transitions, set up SIR values for next time step
            // Out of S:
            if (RNG(gen) < SIR[0]->trans_S_I(S,I,N,time[i],m_dt)) {S -= 1; I += 1;}

            if (m_p->m_f != 0)  // if f = 0 not use this transition
            {
                if (RNG(gen) < SIR[0]->trans_S_R(m_dt)) {S -= 1; R += 1;}
            }

            if (RNG(gen) < SIR[0]->trans_S_D(S,m_dt)) {S -= 1;}
            if (RNG(gen) < SIR[0]->trans_E_S(N,m_dt)) {S += 1;}

            // Out of I:
            if (RNG(gen) < SIR[1]->trans_I_R(I,m_dt)) {I -= 1; R += 1;}
            if (RNG(gen) < SIR[1]->trans_I_D(I,m_dt)) {I -= 1;}

            if (m_p->m_dI != 0) // if dI = 0 not use this transition
            {
                if (RNG(gen) < SIR[1]->trans_I_DI(I,m_dt)) {I -= 1;}
            }

            // Out of R:
            if (RNG(gen) < SIR[2]->trans_R_S(R,m_dt)) {R -= 1; S += 1;}
            if (RNG(gen) < SIR[2]->trans_R_D(R,m_dt)) {R -=1;}
        }
        //cout << MC_time.back() << endl;
    }
    cout << "MC done in " << (double(clock()-timestart)/double(CLOCKS_PER_SEC)) << " seconds.\n" << endl;
}

void MonteCarlo::write_averages(writeme *write)
{
    m_p->config_write(write,"SIR_MC");
    write->add_double("sigS",avg_sigS);
    write->add_double("sigI",avg_sigI);
    write->add_double("sigR",avg_sigR);
    string aname = m_p->m_afunc->get_name();
    string tempstring = "SIR_MC_";
    write->set_default_filename(tempstring + aname,true,true);

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
