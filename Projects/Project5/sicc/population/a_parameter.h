#ifndef A_PARAMETER_H
#define A_PARAMETER_H

class a_parameter
{
public:
    a_parameter();
    virtual ~a_parameter();

    virtual double a(double t) = 0;
};

#endif // A_PARAMETER_H
