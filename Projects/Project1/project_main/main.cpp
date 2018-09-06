#include <iostream>
#include <armadillo>
#include <cmath>
#include <string>


using namespace std;
using namespace arma;

// Functions
inline double f(double x) {return 100.0*exp(-10.0*x);}
inline double exact_sol(double x) {return 1-(1-exp(-10.0))*x-exp(-10.0*x);}
void forw_backw(uword n,vec &a,vec &b,vec &c,vec &f,vec &sol);
void save_arrays(string filename,uword n, vec datapoints, vec solution);

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
        uword nlong = n;    // Avoiding warning in armadillo statements
        string fileout = outfilename;
        string argument = to_string(i);
        fileout.append(argument);

        // Allocate memory / initialize arrays
        double h = 1.0/(n+1); //step size
        double hh = h*h;
        vec a(nlong-1,fill::ones),b(nlong,fill::ones),c(nlong-1,fill::ones); //diagonals
        vec sol(nlong,fill::zeros),x(nlong,fill::zeros),f_til(nlong);

        // Fill/shape arrays
        a = -1*a; c = -1*c; b = 2*b;

        for (uword j = 0; j < nlong; ++j) {
            x(j) = (j+1)*h;
            f_til(j) = hh*f(x(j));
//            if ( i == exponent){
//                // Only compute and save most accurate exact solution
//                vec exactv(nlong);
//                exactv(j) = exact_sol(x(j));
            }
        forw_backw(nlong,a,b,c,f_til,sol);
        save_arrays(fileout,nlong,x,sol);
        //exactv.save(fileout+"exact.dat",raw_ascii);
    }
    return 0;
}
void forw_backw(uword n,vec &a,vec &b,vec &c,vec &f,vec &sol){
    for (uword i = 1; i < n; ++i ){
        b.at(i) = b.at(i) - (a.at(i-1)*c.at(i-1))/b.at(i-1);
        f.at(i) = f.at(i) - (a.at(i-1)*f.at(i-1))/b.at(i-1);
    }
    sol.at(n-1) = f.at(n-1)/b.at(n-1);
    for (int i = n-2; i >= 0;--i){
        sol.at(i) = (f.at(i)-c.at(i)*sol.at(i+1))/b.at(i);
    }

}
void save_arrays(string filename,uword n, const vec datapoints, const vec solution){
    // Adding endpoints to arrays that are to be saved
    vec outpoints(n+2);vec outsol(n+2);
    outpoints(0)=0.0; outpoints.at(n+1)=1.0;
    outsol(0) = 0.0; outsol.at(n+1)=0.0;
    for (uword i=1;i<=n;i++){
        outsol(i) = solution(i-1);
        outpoints(i) = datapoints(i-1);
    }
    string solfilename = filename + "sol.dat";
    string datafilename = filename + "points.dat";
    outsol.save(solfilename,arma::raw_ascii);
    outpoints.save(datafilename,raw_ascii);
}
