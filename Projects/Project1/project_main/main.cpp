#include <iostream>
#include <armadillo>
#include <cmath>
#include <string>


using namespace std;
using namespace arma;

// Functions
inline double f(double x) {return 100.0*exp(-10.0*x);}
inline double exact_sol(double x) {return 1-(1-exp(-10.0)*x-exp(-10.0*x));}
void forw_backw(int k,vec &a,vec &b,vec &c,vec &f,vec &sol);

int main(int argc, char *argv[])
{
    string outfilename;
    int exponent;

    // Bad ussage test
    if(argc!=3){
        printf("Bad ussage bro; want [number of grid points in base 10, 10^n; data text file name]\n");
        exit(1);
    }
    else{
    outfilename = (argv[1]);
    exponent = atoi(argv[2]);
    }
    for (int i = 1; i <= exponent; ++i ){
        int n = int(pow(10.0,i));
        string fileout = outfilename;
        string argument = to_string(i);
        fileout.append(argument);

        // Allocate memory / initialize arrays
        double h = 1.0/(n); //step size
        double hh = h*h;
        vec a(n,fill::ones),b(n+1,fill::ones),c(n,fill::ones); //diagonals
        vec sol(n+1,fill::zeros),x(n+1,fill::zeros),f_til(n+1);

        // Fill/shape arrays
        a = -1*a; c = -1*c; b = 2*b;
        x(0)=0.0; x(n) = 1.0; sol(0) = 0; sol(n) = 0;
        f_til(0) = hh*f(x(0));f_til(n) = hh*f(x(n));

        for (int j = 1; j < n; ++j) {
            x(j) = j*h;
            f_til(j) = hh*f(x(j));
        }
        forw_backw(n,a,b,c,f_til,sol);
        sol.print();
    }

    return 0;
}
void forw_backw(int k,vec &a,vec &b,vec &c,vec &f,vec &sol){
    for (int i = 1; i < k; ++i ){
        b(i) = b(i) - (a(i-1)*c(i-1))/b(i-1);
        f(i) = f(i) - (a(i-1)*f(i-1))/b(i-1);
    }
    sol(k) = f(k)/b(k);
    for (int i = k-1; i>0;--i){
        sol(i) = (f(i)-c(i)*sol(i+1))/b(i);
    }

}
