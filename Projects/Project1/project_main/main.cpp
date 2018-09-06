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
void gauss_general(uword n,vec &a,vec &b,vec &c,vec &f,vec &sol);
void save_arrays(string filename,uword n, vec datapoints, vec solution);
void gauss_specific(int n, vec &b, vec &f, vec &u);
void arma_lu(int n,int a,int b,int c,vec f,vec datapoints);

int main(int argc, char *argv[])
{
    string outfilename;
    int exponent;
    clock_t start, finish;
    clock_t starttotal,finishtotal;
    starttotal = clock();
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
        string fileoutsimple = fileout;
        fileoutsimple.append(string("simpl"));

        // Allocate memory / initialize arrays
        double h = 1.0/(n+1); //step size
        double hh = h*h;
        vec a(nlong-1,fill::ones),b(nlong,fill::ones),c(nlong-1,fill::ones); //diagonals
        vec sol(nlong,fill::zeros),x(nlong,fill::zeros),f_til(nlong);
        vec b_simpl(nlong,fill::zeros),f_til_simpl(nlong,fill::zeros),u_simpl(nlong,fill::zeros);

        // Fill/shape arrays
        a = -1*a; c = -1*c; b = 2*b;

        for (uword j = 0; j < nlong; ++j) {
            x(j) = (j+1)*h;
            f_til(j) = hh*f(x(j));
            b_simpl(j) = (1.0+(j+1))/(double(j+1));
            }
        f_til_simpl = f_til;
        start = clock();
        gauss_general(nlong,a,b,c,f_til,sol);
        finish = clock();
        double time = double((finish-start))/double(CLOCKS_PER_SEC);
        //cout << "test" << time << endl;
        cout << endl;
        printf("Time used for %dx%d matrix using general method = %.15f\n",n,n,time);

        start = clock();
        gauss_specific(n,b_simpl,f_til_simpl,u_simpl);
        finish = clock();
        time = double((finish-start))/double(CLOCKS_PER_SEC);
        printf("Time used for %dx%d matrix using specific method = %.15f\n",n,n,time);

        if (i<6){
            save_arrays(fileout,nlong,x,sol);
            save_arrays(fileoutsimple,nlong,x,u_simpl);
        }
        // LU-decomp
        arma_lu(n,-1,2,-1,f_til,x);
    }

    finishtotal = clock();
    double timetotal = double (finishtotal-starttotal)/double(CLOCKS_PER_SEC);
    printf("Total time = %.15f\n",timetotal);
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

void arma_lu(int n,int a,int b,int c,vec f,vec datapoints)
{
    uword nlong = n;
    mat A(nlong,nlong,fill::eye);
    mat L(nlong,nlong);
    mat U(nlong,nlong);
    vec x(nlong);
    vec v(nlong);
    A = b*A;    // Set diagonal to value b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <n; j++) {
            if (j==i+1){
                A(i,j) = c;
            }
            if (j==i-1){
                A(i,j) = a;
            }
        }
    }

    lu(L, U, A);
    x = solve(L, f);
    v = solve(U, x);
    // v is the solution
    save_arrays("LU_decomp",nlong,datapoints,v);
}
