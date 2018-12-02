#ifndef RECOVERED_H
#define RECOVERED_H

class Recovered
{
private:
    double m_b,m_c,m_d,m_f;
    int m_N,m_R0;
public:
    Recovered();
    Recovered(int N,int R0,double b, double c, double d, double f);
    ~Recovered();

    double R_n;
    double R_prime();
};

#endif // RECOVERED_H
