#include "a_constant.h"

a_constant::a_constant(double a0_)
{
    m_a = a0_;
}

a_constant::~a_constant()
{

}

double a_constant::a(double t)
{
    return m_a;
}
