#ifndef SOLVER_H
#define SOLVER_H

#include "celestialbody.h"

class Solver
{
public:
    double m_dt;
    double m_steps;
    Solver(double dt, double steps);
    void Euler(class SolarSystem &system);
    void Verlet(class SolarSystem &system);
    void Verlet_perihelion(class SolarSystem &system);

private:
    double rlength;
    double peri_angl;
    double get_perihelion_precession(vec3 position) const;
};

#endif // SOLVER_H
