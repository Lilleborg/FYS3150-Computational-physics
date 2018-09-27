#include <iostream>
#include <armadillo>
#include <cmath>
#include <string>
#include "time.h"

using namespace std;
using namespace arma;

//Functions
double time_it(string user, clock_t &start,clock_t &finish );
void matrix_filling(uword N, double h, mat &A);
void largest_offdiagonal(uword N, mat &A, int &k, int &l, double &max);
void matrix_filling_prototype(uword N, double h, mat &A, string &cmd, double &rho0);
void Jakobi_rotate(uword N, mat &A, int &l, int &k);
void test_largest_offdiagonal();

int main(int argc, char *argv[])
{
    if (argc < 2){
        cout << "--- Please give commands: N, problem1/problem2 ---" << endl;
    }

    //Initialize matrices and parameters
    uword N = uword (atoi(argv[1]));
    string cmd = argv[2]; //Either "problem1" or "problem2"

    if (argc == 4){
        cout << "--- TESTING OPTION STARTED; if argv[3] == 1, only tests will be ran ---" << endl;
        int testing = atoi(argv[3]);
        // Tests:
        test_largest_offdiagonal();
        // Option for exiting:
        if (testing == 1){
            exit(1);
        }
        }

    double rhomax = 8.; double rho0 = 0.; //TEST FOR RHO
    double h = (rhomax-rho0)/N;
    mat A = zeros<mat>(N,N);

    //Function for measuring time
    clock_t start, finish;
    double time,time_anal;

    //Call on void that fills matrix as a Toeplitz
    if (cmd == "problem1"){
        cout << "---Initializing solving of problem 1: A buckling beam---" << endl;
        matrix_filling(N, h, A);
        //cout << "---Our initial matrix A is---" << endl;
        //cout << A << endl;
    }
    if (cmd == "problem2"){
        cout << "---Initializing solving of problem 2: Electron in HO-potential---" << endl;
        matrix_filling_prototype(N, h, A, cmd, rho0);
        //cout << "---Our initial matrix A is---" << endl;
        //cout << A << endl;
    }


    //Check with analytical solutions
    vec eigval; mat eigvec;
    time_anal = time_it(string("begin"),start,finish); //Start clock
    eig_sym(eigval, eigvec, A);
    cout << "The analytical eigenvalues of A are: " << endl;
     cout << "lambda_0 = " << eigval[0] << " lambda_1 = "<< eigval[1] << " lambda_2 = " << eigval[2] << endl;
    time_anal = time_it(string("stop"),start,finish); //Stop clock
    printf("Time spent on finding analytical eigenvalues for dim(A) = %d was t = %f s!\n", N, time_anal);

    //Symmetry transformation
    int k, l;
    double max = 0.0001;
    int iterations = 0; int maxiter = 5*N*N;
    double tolerance = 1E-6;

    time = time_it(string("begin"),start,finish); //Start clock
    while ( iterations <= maxiter && max > tolerance){

        largest_offdiagonal(N, A, k, l, max);
        //cout << "k " << k << "l " << l << endl;
        Jakobi_rotate(N, A, l, k);
        //cout << max << endl;
        //cout << iterations << endl;
        iterations++;
        }

    time = time_it(string("stop"),start,finish); //Stop clock
    printf("Time spent on symmetry transformation for dim(A) = %d was t = %f s!\n", N ,time);

    vec a = diagvec(A, k=0); a = sort(a);
    cout << "---The final matrix A was made with " << iterations << " symmetry transformations and the first eigenvalues are---" << endl;
    cout << "lambda_0 = " << a[0] << " lambda_1 = "<< a[1] << " lambda_2 = " << a[2] << endl; //Extracted eigenvalues from A, transpose the vector and sort it according to values
    return 0;

    }

void Jakobi_rotate(uword N, mat &A, int &l, int &k){
    //Jakobi with a k to honor our dear Jakob <3
    double c, s;

    //Need a test to choose t because t ~ -tau +- tau for large tau
    if ( A(k,l) != 0.0){
        double t, tau;
       tau = (A(l, l)-A(k, k))/(2*A(k,l)); //Calculate tau with max element indices

       if (tau >= 0.){ // t = tan(theta)
           t = 1./(tau + sqrt(1+tau*tau));
       }
       else{
           t = -1./(-tau + sqrt(1+tau*tau));
       }
       c = 1./sqrt(1 + t*t); // c = cos(theta)
       s = c*t; // s = sin(theta)
    }
    else {
       c = 1.0;
       s = 0.0;
    }
    double a_kk, a_ll;
    a_kk = A(k,k); a_ll = A(l,l);

    A(k,k) = a_kk*c*c - 2*A(k,l)*c*s + a_ll*s*s;
    A(l,l) = a_ll*c*c + 2*A(k,l)*c*s + a_kk*s*s;
    A(k,l) = 0; A(l,k)= 0; //By definition

    double a_ik, a_il;
    for (int i = 0; i < N; i++){
        if (i != k && i != l){
         a_ik = A(i,k); a_il = A(i,l);

         A(i,k) = a_ik*c - a_il*s;
         A(i,l) = a_il*c + a_ik*s;
         A(k,i) = A(i,k);
         A(l,i) = A(i,l);
        }
    }
}

void largest_offdiagonal(uword N, mat &A, int &k, int &l, double &max){
    //Finds largest off-diagonal element value in a matrix A
     max = 0;
    for (int i = 0; i < N; i++){
        for (int j = i+1; j < N; j++){
             double a_kl = fabs(A(i,j));
             if (a_kl > max){
                 max = fabs(a_kl); k = i; l = j; // updating k and l values to represent the position of max element in A
             }
        }
    }
}

void matrix_filling_prototype(uword N, const double h, mat &A, string &cmd, double &rho0){
    //Fills an empty matrix as a Toeplitz tridiagonal matrix

    //Fill diagonals for problem 1
    if (cmd == "problem1"){
       double d_val= 2/h*h; double a_val = -1/(h*h);

        A(N-1,N-1) = d_val; A(0,0) = d_val; A(N-2, N-1) = a_val; A(0,1) = a_val;
        for (int i = 1; i < N; i++) {
            A(i, i) = d_val;
            A(i, i-1) = a_val;
            A(i-1,i)= A (i,i-1);
        }
    }
    //Fill diagonals for problem 2
    if (cmd == "problem2"){
       double d_val; double e_val = -1./(h*h);

       A(N-1,N-1) = 2/(h*h) + (rho0 + (N-1)*h)*(rho0 + (N-1)*h);
       A(0,0) = 2./(h*h);
       A(N-2, N-1) = e_val; A(N-1, N-2) = e_val; A(0,1) = e_val;
       for (int i = 1; i < N-1; i++) {
           d_val= 2./(h*h) + (rho0 + i*h)*(rho0 + i*h);
           A(i, i) = d_val;
           A(i, i-1) = e_val;
           A(i-1,i) = A(i,i-1);
       }
    }

}


void test_largest_offdiagonal(){
    uword n = 10; // test dimensions
    mat A(n,n,fill::randu); // fill matrix with random elements
    uword kgoal = 60, lgoal = 10;   // set indices for max value
    int k,l;                        // computed values
    double max;
    A(kgoal,lgoal) = 20.0;          // max value of matrix (not on main diagonal)
    cout << A << endl;
    largest_offdiagonal(n,A,k,l,max);
    if (int(kgoal) != k && int(lgoal) != l){
        printf("Test for largest off-diagonal NOT succesfull!\n");
        printf("Found:\n");
        printf("k = %d, l = %d, max element = %f\n",k,l,max);
        printf("Expected:\n");
        printf("kgoal = %d, lgoal = %d\n",int(kgoal),int(lgoal));
    }
    else{
        printf("Test for largest off-diagonal finished succesfully!\n");
        printf("Found:\n");
        printf("k = %d, l = %d, max element = %f\n",k,l,max);
        printf("Expected:\n");
        printf("kgoal = %d, lgoal = %d\n",int(kgoal),int(lgoal));
    }


}

double time_it(string user,clock_t &start, clock_t &finish){
    double time = 0.;
    if (user == string("begin")){
        start = clock();
        return time;
    }
    if (user == string("stop")){
        finish = clock();
        double time = double(finish-start)/double(CLOCKS_PER_SEC);
        return time;
    }
    return time;
}

//-------------------------OLD VERSION OF MATRIX FILLING-------------------------
void matrix_filling(uword N, const double h, mat &A){
    //Fills an empty matrix as a Toeplitz tridiagonal matrix

    //Initialize values appropriate for project
    double d_val= 2/h*h; double a_val = -1/(h*h);

    //Fill diagonals
    A(N-1,N-1) = d_val; A(0,0) = d_val; A(N-2, N-1) = a_val; A(0,1) = a_val;
    for (int i = 1; i < N; i++) {
        A(i, i) = d_val;
        A(i, i-1) = a_val;
        A(i-1,i)= A (i,i-1);
    }
}