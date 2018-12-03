#include "problem.h"

problem::problem(int N, int S0, int I0, int R0)
{
    m_N = N; m_S0 = S0; m_I0 = I0; m_R0 = R0;
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
}

void problem::set_population()
{
    SIR.clear();
    SIR.push_back(new Susceptibles(m_N,m_S0,m_afunc,m_c,m_d,m_e,m_f));
    SIR.push_back(new Infected(m_N,m_I0,m_afunc,m_b,m_d,m_dI));
    SIR.push_back(new Recovered(m_N,m_R0,m_b,m_c,m_d,m_f));
    this->update_current();
}

void problem::update_current()
{
    for (int i = 0; i <3; i++)
    {
        m_Qs[i] = SIR[i]->get_current();
    }
}

void problem::evolve()
{
    //for (population_group Q : SIR)
    for (int i = 0; i<3; i++)
    {
        solver->RK4(SIR[i],time[0]);
    }
    update_current();
}

void problem::print_current_SIR()
{
   std::cout << "S: " << m_Qs[0] << " , I: " << m_Qs[1] << " , R: " << m_Qs[2] << std::endl;
}

vector <population_group*> problem::get_SIR()
{
    return SIR;
}
