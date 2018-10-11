#include <iostream>
#include <fstream>
#include <cmath>
//#include <math.h>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Declare functions
vector<double> acceleration(vector<double> const& pos);
void solver_earth_sun(u_long n,double step, vector<vector<double>> (*method)(double h,vector<double> const &pos,vector<double> const &vel,vector<double> const &acc));
vector<vector<double>> step_forward_Euler(double h, const vector<double> &pos, const vector<double> &vel, const vector<double> &acc);
void output(double time, const vector<double> &pos, const vector<double> &vel, const vector<double> &acc);
void get_initials(u_long body_number, vector<double>& pos,vector <double>& vel,vector <double>& acc);

// Global constants
const double AU = 1.5e11; // AU as [meter]
const double M_sun = 2e30;    // sun mas in [kg]
const double yr = 31536000;   // yr in [s]
const double pi = 3.141592653589793;
const double G_M_sun = double(pi*pi*4);
const double M_earth=6e24; //earth mass in [kg]
ofstream ofile;
//const double *masses = new double[3];



int main(int argc, char *argv[]){
    double end_time = 1.0; //end time for simulation in [yr]
    double h = 1.0/365;  // step size
    string filename;

    // command line arguments
    if (argc <= 2){
        cout << "--- Please give commands: Output base filename; Optional: Step size in days, End time [yr] FIX THIS ---" << endl;
        exit(1);
        // Base Filename used in all outputfiles in begining of name
        // Optional:
        // User defined step size, used to determin length of arrays, defaults to 1 day                                 Number of integration points not included initial condition, such that arrays have length N+1
        // End time for simulation, defaults to 1 yr

    }
    else if (argc == 4) {
        h = atof(argv[2])/365.0; end_time = atof(argv[3]);
    }
    else if (argc == 3){
        h = atof(argv[2])/365.0;  // only user defined step size, end_time defaults to 1
    }
    filename = argv[1];
    ofile.open(filename);

    //TESTING NOT CURRENTLY IN USE
    if (argc == 6){
        cout << "--- TESTING OPTION STARTED; if argv[3] == 1, only tests will be ran, FIX THIS ---" << endl;
        int testing = atoi(argv[3]);
        // Tests:

        // Option for exiting:
        if (testing == 1){
            exit(1);
        }
    }
    // initializing
    u_long n = u_long(end_time/h);  // number of points
    if (n>1e4){
        cout << "Large number of points! n = " << n << endl;
    //vector <double> pos(3,0); vector <double> vel(3,0); vector <double> acc(3,0);
    }
    solver_earth_sun(n,h,step_forward_Euler);
    ofile.close();
    cout << "Main ended" << endl; // when developing REMOVE LATER
    return 0;
}
double l2_norm(vector<double> const& u) {
    double accum = 0.;
    for (u_long i = 0; i < u.size(); ++i) {
        accum += u[i] * u[i];
    }
    return sqrt(accum);
}

void get_initials(u_long body_number, vector<double>& pos,vector <double>& vel,vector <double>& acc){
    u_long number_of_bodies = 2;

    vector<vector<double>> initial_pos(number_of_bodies,vector<double>(3));        // may be extended to include more bodies
    vector<vector<double>> initial_vel(number_of_bodies,vector<double>(3));
    vector<vector<double>> initial_acc(number_of_bodies,vector<double>(3));
    // i in [0,9], 0 = sun, 9 = pluto
    // change to read from file in future
    //Sun
    initial_pos[0][0] = 0.0; initial_pos[0][1] = 0.0; initial_pos[0][2] = 0.0;
    initial_vel[0][0] = 0.0; initial_vel[0][1] = 0.0; initial_vel[0][2] = 0.0;
    initial_acc[0][0] = 0.0; initial_acc[0][1] = 0.0; initial_acc[0][2] = 0.0;

    //Eearth
    initial_pos[1][0] = -1.752200603881933E-01; initial_pos[1][1] = 9.675633320786794E-01;
    initial_pos[1][2] = -3.799746898985921E-05;
    initial_vel[1][0] = -1.720124877602163E-02; initial_vel[1][1] = -3.130282140938300E-03;
    initial_vel[1][2] = -2.538590515321615E-07;
    initial_acc[1] = acceleration((initial_pos[1]));

    pos = initial_pos[body_number];
    cout << "norm pos " << l2_norm(pos) << endl;
    vel = initial_vel[body_number];
    acc = initial_acc[body_number];
}

void solver_earth_sun(u_long n,double step, vector<vector<double>> (*method)(double h,vector<double> const &pos,vector<double> const &vel,vector<double> const &acc)){
    // maybe not save hole vectors for each of these? save to file on the go? (different from euler to verlet)
    vector<vector<double>> r_vec(n,vector<double> (3));
    vector<vector<double>> v_vec(n,vector<double> (3));
    vector<vector<double>> a_vec(n,vector<double> (3));
    get_initials(1,r_vec[0],v_vec[0],a_vec[0]);

    ofile << setw(10) << "t" << setw(20) << "x" << setw(20) << "y" << setw(20) << "z"<< endl;
    output(0,r_vec[0],v_vec[0],a_vec[0]);
    for (u_long k = 1; k < n; ++k) {
        vector <vector<double>> next = method(step,r_vec[k-1],v_vec[k-1],a_vec[k-1]);
        r_vec[k] = next[0];
        v_vec[k] = next[1];
        a_vec[k] = acceleration(r_vec[k]);
        output(k*step,r_vec[k],v_vec[k],a_vec[k]);
    }
    cout << "solver earth sun loop finished" << endl;
}
vector<double> acceleration(vector<double> const& pos){
    // CURRENTLY ONLY FUCTIONS FOR EARTH-SUN SYSTEM
    // generalize to calculate between any two bodies with each given pos and mass
    vector<double> acc(3,0);
    double r = l2_norm(pos);
    for (u_long k = 0; k<3;++k){
        acc[k] = -G_M_sun*pos[k]/(pow(r,3)*M_earth);
    }
    return acc;
}

vector<vector<double>> step_forward_Euler(double h,vector<double> const& pos,vector<double> const& vel,vector<double> const& acc){
    // could be expanded to return vel as well
    vector <vector<double>> next(2,vector<double> (3));
    for (u_long k = 0; k <3; k++){
        next[1][k] = vel[k] + h*acc[k];
        next[0][k] = pos[k] + h*vel[k];
    }
    return next;
}
/*
void step_velocity_Verlet(double h,vector<double>& pos,vector<double>& vel,double* acc){

}
*/
void output(double time, const vector<double> &pos, const vector<double> &vel, const vector<double> &acc)
{

  ofile << setiosflags(ios::showpoint | ios::uppercase);
  ofile << setw(15) << setprecision(8) << time;
  for (const auto &e : pos) ofile << setw(20) << setprecision(8)<< e;
  //for (const auto &e : vel) ofile << setw(15) << setprecision(8)<< e;
  for (const auto &e : acc) ofile << setw(20) << setprecision(8)<< e;
  ofile << endl;
  /*
  for (u_long k = 0; k<3; ++k){
      ofile << setw(15) << setprecision(8) << pos[k];
  }*/
  /*
  }
  */
  /*
  for (u_long k = 0; k<3; ++k){
      ofile << setw(15) << setprecision(8) << vel[k];
  ofile << setw(15) << setprecision(8) << l2_norm(acc) << endl; // should be constant
}*/
}


