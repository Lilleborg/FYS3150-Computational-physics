#include "problem.h"

problem::problem(int N, int S0, int I0, string name_, int R0)
{
    m_N = N; m_S0 = S0; m_I0 = I0; m_R0 = R0;
    name = name_;
}

problem::~problem()
{
    delete m_afunc;
    for (int i=0; i<3;i++)
    {
        delete SIR[i];
    }
}

void problem::set_parameters(double b, double c, double d, double dI, double e, double f)
{
    m_b = b; m_c = c; m_d = d; m_dI = dI; m_e = e; m_f = f;
    m_params["b"] = m_b;
    m_params["c"] = m_c;
    if (m_d != 0) m_params["d"] = m_d;
    if (m_dI != 0) m_params["dI"] = m_dI;
    if (m_e != 0) m_params["e"] = m_e;
    if (m_f != 0) m_params["f"] = m_f;
}

void problem::set_timing(double dt, double T, double T0)
{
    time.clear();
    m_dt = dt; m_T = T; m_T0 = T0;
    m_nr_steps = int(ceil((m_T-m_T0)/m_dt));
    for (double i = 0; i <=m_T; i+=m_dt)
    {
        time.push_back(i);
    }
    solver = new ODEsolver(this,m_dt);
    current_step = 0;
}

void problem::set_population()
{
    SIR.clear();
    SIR.push_back(new Susceptibles(m_N,m_S0,m_afunc,m_c,m_d,m_e,m_f));
    SIR.push_back(new Infected(m_N,m_I0,m_afunc,m_b,m_d,m_dI));
    SIR.push_back(new Recovered(m_N,m_R0,m_b,m_c,m_d,m_f));
    this->update_current();
    current_step = 0;
}

void problem::update_current()
{
    for (int i = 0; i <3; i++)
    {
        m_Qs[i] = SIR[i]->get_current();
    }
    update_all();
}

void problem::update_all()
{
    S_vector.push_back(m_Qs[0]);
    I_vector.push_back(m_Qs[1]);
    R_vector.push_back(m_Qs[2]);
}

void problem::evolve(double t)
{
    for (int i = 0; i<3; i++)
    {
        solver->RK4(SIR[i],t);
    }
    update_current();
    current_step += 1;
}

void problem::evolve(int i)
{
    evolve(time[i]);
}

bool problem::test_total_population()
{
    test_sum = 0;
    double tol = 5;
    for (double& q : m_Qs)
    {
        test_sum += q;
    }
    return fabs(test_sum-m_N)>tol;
}

void problem::evolve_full(bool debug)
{
    cout << "Running full simulation of problem " << name << " with " << m_nr_steps << " steps\n";
    cout << "..." << endl;
    clock_t timestart = clock();
    for (int i = 0; i < m_nr_steps;i++)
    {
        this->evolve(i);
        if (debug)
        {
            if (i%int(m_nr_steps/1000) == 0)
            {
                if (this->test_total_population())
                {
                    cout << "-------------------------------------------------------------------\n";
                    cout << "Terminating run as total number of people has changed significantly\n";
                    cout << "-------------------------------------------------------------------\n";
                    cout << "Total population initially" << m_N << ", current population " << test_sum << "\n";
                    cout << "at time " << time[i] << " ran " << i << " steps." << endl;
                    break;
                }
            }
        }
    }
    cout << "Simulation done in " << (double(clock()-timestart)/double(CLOCKS_PER_SEC)) << " seconds.\n" << endl;
}

void problem::config_write(writeme *write,string filenamestart)
{
    write->clear_default_filename();
    write->clear_subpath();
    write->set_subpath(name + "/");
    for (const auto& e : m_params)
    {
        write->add_double(e.first,e.second);
    }
    write->add_int("N", m_N);
    write->set_default_filename(filenamestart + "_" + m_afunc->get_name(),true,true);
}

void problem::write_SIR(writeme *write, bool config)
{
    if (config)
    {
        config_write(write);
    }
    vector<vector<double>> temp;
    temp.push_back(S_vector);
    temp.push_back(I_vector);
    temp.push_back(R_vector);
    write->write_vector_vector(temp);
}

void problem::write_SIR_one_by_one(writeme *write, bool config)
{
    if (config)
    {
        config_write(write,"");
    }
    write->write_double_vector(S_vector,"S");
    write->write_double_vector(I_vector,"I");
    write->write_double_vector(R_vector,"R");
}

void problem::print_current_SIR(bool debug)
{
    if (debug)
    {
        this->test_total_population();
        cout << "At time " << time[current_step] << " index " << current_step << " the sum of current SIR values " << test_sum;
        cout << " vs initial " << m_N << endl;
    }
    cout << "S: " << m_Qs[0] << " , I: " << m_Qs[1] << " , R: " << m_Qs[2] << endl;
}

vector <population_group*> problem::get_SIR()
{
    return SIR;
}
