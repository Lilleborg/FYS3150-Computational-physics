#include "a_constant.h"

a_constant::a_constant(double a0)
{
    m_a = a0;
}

a_constant::~a_constant()
{
}

double a_constant::a(double t)
{
    return m_a;
}

std::string a_constant::get_name()
{
    return name;
}
