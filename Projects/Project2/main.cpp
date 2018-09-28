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
void matrix_filling_prototype(uword N, double h, mat &A, string &cmd, double &rho0, double &w);
void Jakobi_rotate(uword N, mat &A, int &l, int &k);
// Test-functions
void test_largest_offdiagonal();
void test_eigenvals_eigenvec();

int main(int argc, char *argv[])
{
    if (argc < 2){
        cout << "--- Please give commands: N, problem1/problem2/problem3, FIX THIS ---" << endl;
    }

    //TESTING ALL ALGORITHMS
    if (argc == 4){
        cout << "--- TESTING OPTION STARTED; if argv[3] == 1, only tests will be ran ---" << endl;
        int testing = atoi(argv[3]);
        // Tests:
        test_largest_offdiagonal();
        test_eigenvals_eigenvec();
        // Option for exiting:
        if (testing == 1){
            exit(1);
        }
        }

    //FUNCTION FOR MEASURING TIME
    clock_t start, finish;
    double time,time_anal;

    //INITIALIZE PARAMETERS
    uword N = uword (atoi(argv[1]));
    string cmd = argv[2]; //Either "problem1", "problem2", "problem3"
    mat A = zeros<mat>(N,N);
    vec eigval; mat eigvec; //For analytical solutions

    int k, l;
    double max = 0.0001; //Just to get while-loop started
    int iterations = 0; int maxiter = 5*N*N;
    double tolerance = 1E-6;
    vec omega(4); omega(0)=0.001; omega(1)=0.5; omega(2)=1.0; omega(3)=5.0; double w; //Oscillator frequency

    //MAIN ALGORITHM BASED ON CHOSEN PROBLEM TO SOLVE
    if (cmd == "problem1"){
        cout << "---Initializing solving of problem 1: A buckling beam---" << endl;
        double rhomax = 1.; double rho0 = 0.;
        double h = (rhomax-rho0)/N; //STEP SIZE AND VALUES FOR DIMLESS RHO

        w = omega[2]; //Oscillator frequency
        matrix_filling_prototype(N, h, A, cmd, rho0, w);
        //cout << "---Our initial matrix A is---" << endl;
        //cout << A << endl;

        //ANALYTICAL SOLUTIONS
        time_anal = time_it(string("begin"),start,finish); //Start clock
        eig_sym(eigval, eigvec, A);
        time_anal = time_it(string("stop"),start,finish); //Stop clock
        //cout << "The analytical eigenvalues of A are: " << endl;
        //cout << "lambda_0 = " << eigval[0] << " lambda_1 = "<< eigval[1] << " lambda_2 = " << eigval[2] << endl;
        //printf("Time spent on finding analytical eigenvalues for dim(A) = %d was t = %f s!\n", N, time_anal);

        //SAVE ANALYTICAL SOLUTIONS TO FILE

        time = time_it(string("begin"),start,finish); //Start clock
        //SYMMETRY TRANSFORMATION
        while ( iterations <= maxiter && max > tolerance){
            largest_offdiagonal(N, A, k, l, max);
            Jakobi_rotate(N, A, l, k);
            iterations++;
            }
        time = time_it(string("stop"),start,finish); //Stop clock

        //SAVE NUMERICAL SOLUTIONS TO FILE

    }

    if (cmd == "problem2"){
        cout << "---Initializing solving of problem 2: Electron in HO-potential---" << endl;

        double rhomax = 8.; double rho0 = 0.;
        double h = (rhomax-rho0)/N; //STEP SIZE AND VALUES FOR DIMLESS RHO

        w = omega[2]; //Oscillator frequency
        matrix_filling_prototype(N, h, A, cmd, rho0, w);
        //cout << "---Our initial matrix A is---" << endl;
        //cout << A << endl;

        //ANALYTICAL SOLUTIONS
        time_anal = time_it(string("begin"),start,finish); //Start clock
        eig_sym(eigval, eigvec, A);
        time_anal = time_it(string("stop"),start,finish); //Stop clock
        cout << "The analytical eigenvalues of A are: " << endl;
        cout << "lambda_0 = " << eigval[0] << " lambda_1 = "<< eigval[1] << " lambda_2 = " << eigval[2] << endl;
        //printf("Time spent on finding analytical eigenvalues for dim(A) = %d was t = %f s!\n", N, time_anal);

        //SAVE ANALYTICAL SOLUTIONS TO FILE

        time = time_it(string("begin"),start,finish); //Start clock
        //SYMMETRY TRANSFORMATION
        while ( iterations <= maxiter && max > tolerance){
            largest_offdiagonal(N, A, k, l, max);
            Jakobi_rotate(N, A, l, k);
            iterations++;
            }
        time = time_it(string("stop"),start,finish); //Stop clock
        vec a = diagvec(A, k=0); a = sort(a);
        cout << "---The final matrix A was made with " << iterations << " symmetry transformations and the first eigenvalues are---" << endl;
        cout << "lambda_0 = " << a[0] << " lambda_1 = "<< a[1] << " lambda_2 = " << a[2] << endl; //Extracted eigenvalues from A, transpose the vector and sort it according to values


        //SAVE NUMERICAL SOLUTIONS TO FILE

    }

    if (cmd == "problem3"){
        cout << "---Initializing solving of problem 2: Two electrons in HO-potential---" << endl;

        double rhomax = 1.; double rho0 = 0.;
        double h = (rhomax-rho0)/N; //STEP SIZE AND VALUES FOR DIMLESS RHO

        for (int i = 0; i < 4; i++){
            w = omega[i];
            matrix_filling_prototype(N, h, A, cmd, rho0, w);
            cout << "---Our initial matrix A is---" << endl;
            cout << A << endl;

            //ANALYTICAL SOLUTIONS
            time_anal = time_it(string("begin"),start,finish); //Start clock
            eig_sym(eigval, eigvec, A);
            //cout << "The analytical eigenvalues of A are: " << endl;
            //cout << "lambda_0 = " << eigval[0] << " lambda_1 = "<< eigval[1] << " lambda_2 = " << eigval[2] << endl;
            time_anal = time_it(string("stop"),start,finish); //Stop clock
            //printf("Time spent on finding analytical eigenvalues for dim(A) = %d was t = %f s!\n", N, time_anal);

            //SAVE ANALYTICAL SOLUTIONS TO FILE


            time = time_it(string("begin"),start,finish); //Start clock
            //SYMMETRY TRANSFORMATION
            while ( iterations <= maxiter && max > tolerance){
                largest_offdiagonal(N, A, k, l, max);
                Jakobi_rotate(N, A, l, k);
                iterations++;
                }
            time = time_it(string("stop"),start,finish); //Stop clock

            //SAVE NUMERICAL SOLUTIONS TO FILE
        }
    }

    /*
    printf("Time spent on symmetry transformation for dim(A) = %d was t = %f s!\n", N ,time);

    vec a = diagvec(A, k=0); a = sort(a);
    cout << "---The final matrix A was made with " << iterations << " symmetry transformations and the first eigenvalues are---" << endl;
    cout << "lambda_0 = " << a[0] << " lambda_1 = "<< a[1] << " lambda_2 = " << a[2] << endl; //Extracted eigenvalues from A, transpose the vector and sort it according to values
    */

    return 0;
    }

//----- VOIDS AND FUNCTIONS -----------------------------------------------------------------------

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
        for (int j = i+1; j < N; j++){ //Loop over upper triangular part of matrix A
             double a_kl = fabs(A(i,j));
             if (a_kl > max){
                 max = fabs(a_kl); k = i; l = j; // updating k and l values to represent the position of max element in A
             }
        }
    }
}

void matrix_filling_prototype(uword N, const double h, mat &A, string &cmd, double &rho0, double &w){
    //Fills an empty matrix as a Toeplitz tridiagonal matrix

    //Fill diagonals for problem 1 - BUCKLING BEAM
    if (cmd == "problem1"){
       double d_val= 2/h*h; double a_val = -1/(h*h);

        A(N-1,N-1) = d_val; A(0,0) = d_val; A(N-2, N-1) = a_val; A(0,1) = a_val;
        for (int i = 1; i < N; i++) {
            A(i, i) = d_val;
            A(i, i-1) = a_val;
            A(i-1,i)= A (i,i-1);
        }
    }
    //Fill diagonals for problem 2 - ONE ELECTRON IN HO
    if (cmd == "problem2"){
       double d_val; double e_val = -1./(h*h);

       A(N-1,N-1) = 2/(h*h) + w*w*(rho0 + (N-1)*h)*(rho0 + (N-1)*h);
       A(0,0) = 2./(h*h) + w*w*(rho0 + h)*(rho0 + h);
       A(N-2, N-1) = e_val; A(N-1, N-2) = e_val; A(0,1) = e_val;
       for (int i = 1; i < N-1; i++) {
           d_val= 2./(h*h) + w*w*(rho0 + (i+1)*h)*(rho0 + (i+1)*h);
           A(i, i) = d_val;
           A(i, i-1) = e_val;
           A(i-1,i) = A(i,i-1);
       }
    }
    //Fill diagonals for problem 3 - TWO ELECTRONS IN HO
    if (cmd == "problem3"){
       double d_val; double e_val = -1./(h*h);

       A(N-1, N-1) = 2/(h*h) + w*w*(rho0 + (N-1)*h)*(rho0 + (N-1)*h) + 1./(rho0 + (N-1)*h); // A(i,i) = 2/h^2 + w^2*rho_i^2 + 1/rho_i
       A(0, 0) = 2./(h*h) + w* w* ( rho0 + h )*( rho0 + h) + 1./(rho0 + h);
       A(N-2, N-1) = e_val; A(N-1, N-2) = e_val; A(0,1) = e_val;
       for (int i = 1; i < N-1; i++) {
           d_val= 2./(h*h) + w*w*(rho0 + (i+1)*h)*(rho0 + (i+1)*h) + 1./(rho0 + (i+1)*h);
           A(i, i) = d_val;
           A(i, i-1) = e_val;
           A(i-1,i) = A(i,i-1);
       }
    }
}

void test_eigenvals_eigenvec(){
    uword n = 4;
    int in = int(n);
    int iterations = 5*in*in,k,l,i=0;
    double max = 1, tol = 1e-5;
    mat A(n,n,fill::randu);
    mat B = A.t()*A;    // B is symmetric

    vec eigval;
    mat eigvec;
    eig_sym(eigval,eigvec,B);
    //cout << eigval << " " << eigvec << endl;
    while (i < iterations && max > tol){
        largest_offdiagonal(n,B,k,l,max);
        Jakobi_rotate(n,B,l,k);
        i++;
        if (i % 100 == 0){  // only checks orthogonality for every 100th

        }
    }
    vec calc_eigenval = sort(diagvec(B));
    //cout << calc_eigenval << endl;
    if (approx_equal(calc_eigenval,eigval,"absdiff",tol)){
        printf("Test for eigenvalues from Jakobis method finished succesfully!\n");
        cout << "Calculated eigenvalues" << calc_eigenval.t() << endl;
        cout << "Expected eigenvalues" << eigval.t() << endl;
    }
    else{
        printf("Test for eigenvalues from Jakobis method NOT succesfull\n");
        printf("Found:\n");
        for (int i = 0; i < in; ++i) {
            printf("Eigenvalue %d: calc = %f, expected = %f\n",i,calc_eigenval[i],eigval[i]);
        }
    }
}

void test_largest_offdiagonal(){
    uword n = 10; // test dimensions
    mat A(n,n,fill::ones); // fill matrix with random elements
    uword kgoal = n/2-2, lgoal = n/2+2;   // set indices for max value
    int k,l;                        // computed values
    double max;
    A(kgoal,lgoal) = 200.0;          // max value of matrix (not on main diagonal)

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

/*
void save_arrays(string filename,uword N, const vec datapoints, const vec solution, int data){
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
*/

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
