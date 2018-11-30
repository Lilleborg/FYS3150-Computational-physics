#ifndef POPULATIONS_H
#define POPULATIONS_H
#include<vector>
#include<string>
#include "vec3.h"
using namespace std;

class Populations
{
public:
    //TRANSMISSION RATES
    double a;
    double b;
    double c;
    int N;

    //POPULATION NAME
    string name;

    //CURRENT VALUES ODES
    vec3 u_i;

    //VECTOR FOR STORING SOLUTIONS TO DIFFERENTIAL EQUATIONS
    //u[0] = S, u[1] = I, u[2] = R
    vector<vec3> u;

    //How to deal with intial conditions?
    Populations(double a_, double b_, double c_, vec3 u0_, int N_, string name_);

    vec3 SIR_a(vec3 u, double t);
};

#endif // POPULATIONS_H
