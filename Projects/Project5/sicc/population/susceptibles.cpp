#include "susceptibles.h"
#include <iostream>

Susceptibles::Susceptibles()
{
}

Susceptibles::~Susceptibles()
{
}

Susceptibles::Susceptibles(int N, int S0, a_parameter *a, double c, double d, double e, double f)
{
    m_N = N; m_S0 = S0;
    m_c = c; m_d = d; m_e = e; m_f = f;
    m_a_param = a;
    current = double(m_S0);
}

double Susceptibles::prime(vector <double> Qs, double t)
{
    //std::cout << m_c*Qs[2]-m_a_param->a(t)*Qs[0]*Qs[1]/m_N<< std::endl;//-m_d*Qs[0]+m_e*m_N-m_f << std::endl;
    return m_c*Qs[2]-m_a_param->a(t)*Qs[0]*Qs[1]/m_N-m_d*Qs[0]+m_e*m_N-m_f;
}

void Susceptibles::add_to_current(double prev)
{
//    std::cout << "In add to current S\n";
//    std::cout << current << " " << prev << std::endl;

    current += prev;

//    std::cout << current << std::endl;
}

double Susceptibles::get_current()
{
    return current;
}

