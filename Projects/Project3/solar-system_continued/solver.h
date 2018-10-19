#ifndef SOLVER_H
#define SOLVER_H

class Solver
{
public:
    double m_dt;
    double m_steps;
    Solver(double dt, double steps);
    void Euler(class SolarSystem &system);
    void Verlet(class SolarSystem &system);
};

#endif // SOLVER_H
