#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <cstring>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace arma;
using namespace std;

uword PeriodicBoundary(uword i, uword limit, int add);
void initialize_new_round(uword Nspins, imat& Lattice, double &Energy, double &MagneticMom, string Fillstyle);
void metropolis(uword Nspins, __1::mt19937_64& gen, imat &Lattice, vec &w, double &E, double &M);
vec normalizing_expectations(double const T, double const MC, int const L, vec const Exp_vals);

void results_per_mc(double *quantity,int MC, string filename);
void write_exp_values(const double T, const int MC, int L, vec Exp_vals, ofstream &ofile, string filename);
void write_double_vector(vector<double> quantity,string filenamestart);

#endif // FUNCTIONS_H
