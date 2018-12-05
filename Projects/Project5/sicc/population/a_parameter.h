#ifndef A_PARAMETER_H
#define A_PARAMETER_H
#include <string>

class a_parameter
{
public:
    a_parameter();
    virtual ~a_parameter();

    virtual std::string get_name() = 0;
    virtual double a(double t) = 0;
};

#endif // A_PARAMETER_H
