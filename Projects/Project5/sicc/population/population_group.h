#ifndef POPULATION_GROUP_H
#define POPULATION_GROUP_H

#include "population/a_parameter.h"
#include <vector>

using std::vector;

class population_group
{
public:
    population_group(); 
    virtual ~population_group();

    virtual double get_current() = 0;
    virtual double prime(vector <double> Qs, double t) = 0;
    virtual void add_prime(vector <double> Qs, double t) = 0;

};

#endif // POPULATION_GROUP_H
