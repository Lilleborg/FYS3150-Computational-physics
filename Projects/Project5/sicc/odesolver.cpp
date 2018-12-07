#include "odesolver.h"
#include "problem.h"

ODEsolver::ODEsolver(problem *p_, double dt)
{   
    m_dt = dt;
    m_problem = p_;
}

ODEsolver::~ODEsolver()
{
}

vector<double> ODEsolver::vec_pluss(const vector<double> vec, double pluss)
{
    vector <double> temp;
    for (int i = 0; i<3; i++)
    {
        temp.push_back(vec[i] + pluss);
    }
    return temp;
}

//void ODEsolver::Euler(population_group *p)
//{
//}

void ODEsolver::RK4(population_group *p, double t)
{
    get_ks(p,t);
    p->add_to_current(1.0/6*(ks[0]+2.0*ks[1]+2.0*ks[2]+ks[3]));
}

void ODEsolver::get_ks(population_group *p, double t)
{
    ks.clear();
    ks[0] = m_dt*p->prime(m_problem->m_Qs, t);
    ks[1] = m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks[0]/2.0), t + m_dt/2.);
    ks[2] = m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks[1]/2.0), t + m_dt/2.);
    ks[3] = m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks[2]), t + m_dt);
}

