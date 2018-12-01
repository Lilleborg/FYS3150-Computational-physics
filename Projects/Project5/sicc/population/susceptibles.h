#ifndef SUSCEPTIBLES_H
#define SUSCEPTIBLES_H

#include "population/population_group.h"

class Susceptibles : public population_group
{
public:

    // Init
    Susceptibles(double a0,double c, double d, double e, double f,double );

    // Parameters
    double a0;
    double a();
    double a(double t);

};


#endif // SUSCEPTIBLES_H
