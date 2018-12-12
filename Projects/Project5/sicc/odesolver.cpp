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

vector<double> ODEsolver::vec_pluss(const vector<double> vec, double x, double y, double z)
{
    vector<double> temp;
    temp.push_back(vec[0] + x);
    temp.push_back(vec[1] + y);
    temp.push_back(vec[2] + z);
    return temp;
}

//void ODEsolver::Euler(population_group *p)
//{
//}

void ODEsolver::RK4(population_group *p, double t)
{
    get_ks(p,t);
//    std::cout << "ks values \n" << ks[0] << " " << ks[1] << " " << ks[2] << " " << ks[3] << std::endl;
//    std::cout << "ks size\n" << ks.size() << endl;
//    cout << "current value before add\n";
//    cout << p->get_current() << endl;
//    cout << "value added\n";
//    cout << 1.0/6*(ks[0]+2.0*ks[1]+2.0*ks[2]+ks[3]) << endl;

    p->add_to_current(1.0/6*(ks[0]+2.0*ks[1]+2.0*ks[2]+ks[3]));

//    cout << "current value after add\n" << endl;
//    cout << p->get_current() << endl;
    //p->add_to_current(1);
}

void ODEsolver::RK4(vector<population_group*> SIR,double t)
{
    k_S.push_back(m_dt*SIR[0]->prime(m_problem->m_Qs, t));
    k_I.push_back(m_dt*SIR[1]->prime(m_problem->m_Qs, t));
    k_R.push_back(m_dt*SIR[2]->prime(m_problem->m_Qs, t));

    k_S.push_back(m_dt*SIR[0]->prime(vec_pluss(m_problem->m_Qs,k_S.back()/2.0,k_I.back()/2.0,k_R.back()/2.0), t + m_dt/2));
    k_I.push_back(m_dt*SIR[1]->prime(vec_pluss(m_problem->m_Qs,k_S.back()/2.0,k_I.back()/2.0,k_R.back()/2.0), t + m_dt/2));
    k_R.push_back(m_dt*SIR[2]->prime(vec_pluss(m_problem->m_Qs,k_S.back()/2.0,k_I.back()/2.0,k_R.back()/2.0), t + m_dt/2));

    k_S.push_back(m_dt*SIR[0]->prime(vec_pluss(m_problem->m_Qs,k_S.back()/2.0,k_I.back()/2.0,k_R.back()/2.0), t + m_dt/2));
    k_I.push_back(m_dt*SIR[1]->prime(vec_pluss(m_problem->m_Qs,k_S.back()/2.0,k_I.back()/2.0,k_R.back()/2.0), t + m_dt/2));
    k_R.push_back(m_dt*SIR[2]->prime(vec_pluss(m_problem->m_Qs,k_S.back()/2.0,k_I.back()/2.0,k_R.back()/2.0), t + m_dt/2));

    k_S.push_back(m_dt*SIR[0]->prime(vec_pluss(m_problem->m_Qs,k_S.back(),k_I.back(),k_R.back()), t + m_dt));
    k_I.push_back(m_dt*SIR[1]->prime(vec_pluss(m_problem->m_Qs,k_S.back(),k_I.back(),k_R.back()), t + m_dt));
    k_R.push_back(m_dt*SIR[2]->prime(vec_pluss(m_problem->m_Qs,k_S.back(),k_I.back(),k_R.back()), t + m_dt));

    SIR[0]->add_to_current(1.0/6*(k_S[0]+2.0*k_S[1]+2.0*k_S[2]+k_S[3]));
    SIR[1]->add_to_current(1.0/6*(k_I[0]+2.0*k_I[1]+2.0*k_I[2]+k_I[3]));
    SIR[2]->add_to_current(1.0/6*(k_R[0]+2.0*k_R[1]+2.0*k_R[2]+k_R[3]));

    k_S.clear();
    k_I.clear();
    k_R.clear();
}

void ODEsolver::get_ks(population_group *p, double t)
{
    //cout << "Before ks clear\n" << ks.size() << endl;
    ks.clear();
    //cout << "after ks clear\n" << ks.size() << endl;

    ks.push_back(m_dt*p->prime(m_problem->m_Qs, t));
    ks.push_back(m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks.back()/2.0), t + m_dt/2.));
    ks.push_back(m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks.back()/2.0), t + m_dt/2.));
    ks.push_back(m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks.back()), t + m_dt));

    //cout << "after ks fill\n" << ks.size() << endl;


    //ks[0] = m_dt*p->prime(m_problem->m_Qs, t);
    //ks[1] = m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks[0]/2.0), t + m_dt/2.);
    //ks[2] = m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks[1]/2.0), t + m_dt/2.);
    //ks[3] = m_dt*p->prime(vec_pluss(m_problem->m_Qs, ks[2]), t + m_dt);
}

