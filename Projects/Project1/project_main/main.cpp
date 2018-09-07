#include <iostream>
#include <armadillo>
#include <cmath>
#include <string>
#include "time.h"


using namespace std;
using namespace arma;

// Functions
inline double f(double x) {return 100.0*exp(-10.0*x);}
inline double exact_sol(double x) {return 1-(1-exp(-10.0))*x-exp(-10.0*x);}
double time_it(string user, clock_t &start,clock_t &finish );
double max_rel_error(vec sol,vec exact);
void gauss_general(uword n,vec &a,vec &b,vec &c,vec &f,vec &sol);
void save_arrays(string filename,uword n, vec datapoints, vec solution, int data = 0);
void gauss_specific(int n, vec &b, vec &f, vec &u);
void arma_lu(int expo,int a,int b,int c,vec f,vec datapoints);


int main(int argc, char *argv[])
{
    string outfilename;
    int exponent;
    clock_t start, finish;
    clock_t starttotal,finishtotal;
    double time,timespes,timetot;
    double time_diff = double (1e-8);
    timetot = time_it(string("begin"),starttotal,finishtotal);
    // Bad ussage test
    if(argc!=3){
        printf("Bad ussage bro; want [number of grid points in base 10, 10^n; data text file name]\n");
        exit(1);
    }
    else{
        outfilename = (argv[1]);
        exponent = atoi(argv[2]);
    }
    mat errors(exponent,2);
    if (exponent == int(7)){
        cout << "exponent = " << exponent << ". Saving errors!" << endl;
    }
    for (int i = 1; i <= exponent; ++i ){
        int n = int(pow(10.0,i));
        cout << "For a " << n << "x" << n << " matrix, n= 10^" << i << ":" << endl;
        uword nlong = n;    // Avoiding warning in armadillo statements
        string fileout = outfilename;
        string argument = to_string(i);
        fileout.append(argument);
        string fileoutsimple = fileout;
        fileoutsimple.append(string("simpl"));

        // Allocate memory / initialize arrays
        double h = 1.0/(n+1); //step size
        double hh = h*h;
        vec a(nlong-1,fill::ones),b(nlong,fill::ones),c(nlong-1,fill::ones); //diagonals
        vec sol(nlong,fill::zeros),x(nlong,fill::zeros),f_til(nlong);
        vec b_simpl(nlong,fill::zeros),f_til_simpl(nlong,fill::zeros),u_simpl(nlong,fill::zeros);
        vec exact(nlong);

        // Fill/shape arrays
        a = -1*a; c = -1*c; b = 2*b;

        for (uword j = 0; j < nlong; ++j) {
            x(j) = (j+1)*h;
            f_til(j) = hh*f(x(j));
            b_simpl(j) = (1.0+(j+1))/(double(j+1));
            exact(j) = exact_sol(x(j));
        }
        f_til_simpl = f_til;
        vec f_LU = f_til;

        time = time_it(string("begin"),start,finish);
        gauss_general(nlong,a,b,c,f_til,sol);
        time = time_it(string("stop"),start,finish);
        printf("Time used general method = %.7f\n",time);

        timespes = time_it(string("begin"),start,finish);
        gauss_specific(n,b_simpl,f_til_simpl,u_simpl);
        timespes = time_it(string("stop"),start,finish);
        printf("Time used specific method = %.7f\n",timespes);
        if (time-timespes < time_diff){
            cout << "The general method is as fast as the specific method!" << endl;
        }
        else{
        printf("The specific method is = %.15f s faster than the general\n",(time-timespes));
        }
        if (exponent == int(7)){
            errors.at(i-1,0) = max_rel_error(u_simpl,exact);
            errors(i-1,1) = h;
        }

        if (i<4){
            //save_arrays(fileoutsimple,nlong,x,u_simpl);
            save_arrays(fileout,nlong,x,sol,i);
        }
        if (i<4){
            // LU-decomp
            time = time_it(string("begin"),start,finish);
            arma_lu(i,-1,2,-1,f_LU,x);
            time = time_it(string("stop"),start,finish);
            printf("Time used LU-decomposition = %.7f\n",n,n,time);
        }

    }
    if (exponent == int(7)){
        errors.save(string("max_rel_errors_").append(to_string(exponent)).append(".dat"),raw_ascii);
    }
    timetot = time_it(string("stop"),starttotal,finishtotal);
    printf("Total time = %.7f\n",timetot);
    return 0;
}
void gauss_general(uword n,vec &a,vec &b,vec &c,vec &f,vec &sol){
    double factor;
    for (uword i = 1; i < n; ++i ){
        factor = a[i-1]/b[i-1];
        b[i] = b[i] - c[i-1]*factor;
        f[i] = f[i] - factor*f[i-1];
    }
    sol[n-1] = f[n-1]/b[n-1];
    for (int i = n-2; i >= 0;--i){
        sol[i] = (f[i]-c[i]*sol[i+1])/b[i];
    }

}
void gauss_specific(int n, vec &b, vec &f, vec &u){
    for (int i = 1; i < n; i++){
        f[i] = f[i] + f[i-1]/b[i-1];
    }
    u(n-1) = f(n-1)/b(n-1);
    for (int i = n-2; i >= 0; --i) {
        u[i] = (f[i]+u[i+1])/b[i];
    }
}

void save_arrays(string filename,uword n, const vec datapoints, const vec solution, int data){
    // Adding endpoints to arrays that are to be saved
    vec outsol(n+2);
    outsol(0) = 0.0; outsol.at(n+1)=0.0;
    for (uword i=1;i<=n;i++){
        outsol(i) = solution(i-1);
    }
    string solfilename = filename + "sol.dat";
    string datafilename = filename + "points.dat";
    outsol.save(solfilename,arma::raw_ascii);
    if (data != 0){
        vec outpoints(n+2);
        outpoints(0)=0.0; outpoints.at(n+1)=1.0;
        for (uword i = 1; i <=n; i++){
            outpoints(i) = datapoints(i-1);
        }
        outpoints.save(datafilename,raw_ascii);

    }
}

void arma_lu(int expo,int a,int b,int c,const vec f,const vec datapoints)
{
    int n = int(pow(10.0,expo));
    uword nlong = n;
    string n_string = to_string(expo);
    mat A(nlong,nlong,fill::eye);
    mat L(nlong,nlong);
    mat U(nlong,nlong);
    vec y(nlong);
    vec v(nlong);
    A = b*A;    // Set main diagonal to value b
    // Set lower and upper diagonal to a and c:
    A(nlong-1,nlong-2) = a; A(nlong-2,nlong-1) = c; A(0,1) = c;
    for (int i = 1; i < n-1; i++) {
        A(i,i+1) = c;
        A(i,i-1) = a;
    }
    // Ax = f,
    lu(L, U, A);
    // Ly = f
    y = solve(L, f);
    // Uv = y
    v = solve(U, y);
    // v is the solution
    save_arrays(string("LU_decomp").append(n_string),nlong,datapoints,v);
}
double max_rel_error(vec sol,vec exact){
    double error = max((abs(sol-exact)/abs(exact)));
    return error;
}
double time_it(string user,clock_t &start, clock_t &finish){
    double time = 0.;
    if (user == string("begin")){
        start = clock();
        return time;
    }
    if (user == string("stop")){
        finish = clock();
        double time = double((finish-start))/double(CLOCKS_PER_SEC);
        return time;
    }
    return time;
}
