#ifndef A_CONSTANT_H
#define A_CONSTANT_H

#include "population/a_parameter.h"

class a_constant : public a_parameter
{
private:
    double m_a;
public:
    a_constant(double a0);
    ~a_constant();

    double a(double t);

};

#endif // A_CONSTANT_H
