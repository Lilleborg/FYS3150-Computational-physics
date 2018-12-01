#include "populations.h"

Populations::Populations(double a_, double b_, double c_, vec3 u0_, int N_, string name_)
{
    a = a_;
    b = b_;
    c = c_;
    N = N_;
    u_i = u0_;
    name = name_;

}



vec3 Populations::SIR_a(vec3 u, double t){
    vec3 f;
    double S = u[0];
    double I = u[1];
    double R = u[2];

    f[0] = c*R  - a*S*I/N;
    f[1] = a*S*I/N - b*I;
    f[2] = b*I - c*R;
    return f;
}
