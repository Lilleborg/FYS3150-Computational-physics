#include "problem.h"

problem::problem(int N_, int S0_, int I0_)
{
    N = N_; S0 = S0_; I0 = I0_;
}

problem::~problem()
{
    delete m_afunc;
}

void problem::set_parameters(double a0_,double b_,double c_,double d_,double e_,double f_)
{
    a0 = a0_; b = b_; c = c_; d = d_; e = e_; f = f_;
}
