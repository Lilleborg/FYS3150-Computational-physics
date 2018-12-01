#ifndef POPULATION_GROUP_H
#define POPULATION_GROUP_H

#include <vector>
using std::vector;


class population_group
{
public:
    population_group();
    virtual ~population_group();

    virtual double prime(vector<population_group> u) = 0;
};

#endif // POPULATION_GROUP_H
