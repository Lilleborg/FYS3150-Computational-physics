#ifndef SUSCEPTIBLES_H
#define SUSCEPTIBLES_H

#include "population/population_group.h"

class Susceptibles : public population_group
{
private:
    double a0,c,d,e,f
public:

    // Init
    Susceptibles(double a0_,double c_, double d_, double e_, double f_);

    // Parameters
    double a0;
    double a();
    double a(double t);

};


#endif // SUSCEPTIBLES_H
