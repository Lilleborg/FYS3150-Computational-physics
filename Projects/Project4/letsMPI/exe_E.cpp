#include "mpi.h"
#include <iostream>
#include <iomanip>
#include <armadillo>
#include <string>
#include <random>
#include <cmath>

using namespace std;
using namespace arma;

// DECLARE FUNCTIONS
void initialize_new_round(int Nspins, imat &Lattice, double &Energy, double &MagneticMom,string Fillstyle);
vec normalizing_expectations(double const T, double const MC, int const L, vec const Exp_vals);
void write_exp_values(double const T, int const MC,int L, vec Exp_vals, std::ofstream& ofile,string filename);
int metropolis(uword Nspins,mt19937_64 &gen, imat &Lattice, vec &w, double &E, double &M);

inline uword PeriodicBoundary(uword i, uword limit, int add) { //Taken from Morten
    return (i+limit+add) % (limit);
}
// Set up the uniform distribution for x in [0, 1]
uniform_real_distribution<double> RNG(0.0,1.0);
ofstream ofile;

int main(int nArg, char **Arg)
{

    int numprocs,my_rank;
    MPI_Init (&nArg, &Arg);

    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

    // Allocate variables
    double E,M,T_initial,T_final,T_step,Timestart,Timeend,totaltime;
    int L,MC,idum,MCbeforesample;
    string filename;
    string outfile;

    if (my_rank == 0 && nArg <= 4){
        cout << "Bad usage, need cmd args:\n-- L\n-- MCcycles\n-- MCcycles before sampling\n-- Filename" << endl;
        exit(1);
    }
    if (my_rank == 0 && nArg > 2){  // Initialize with root
        L = atoi(Arg[1]);
        MC = atoi(Arg[2]);
        MCbeforesample = atoi(Arg[3]);
        filename = Arg[4];
        T_initial = 2.24; T_final = 2.29; T_step = 0.0008;

        outfile = filename.append("_L_"+to_string(L)+"_effectiveMC_"+to_string(MC-MCbeforesample)+".txt");
        cout << "Opening " << outfile << " with rank " << my_rank << endl;
        ofile.open(outfile);
    }
    
    // Broadcasting
    MPI_Bcast(&L,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&MC,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&MCbeforesample,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&T_initial,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&T_final,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&T_step,1,MPI_DOUBLE,0,MPI_COMM_WORLD);


    idum = 10+my_rank;   // Individual seeds
    imat Lattice(L,L);
    initialize_new_round(L,Lattice,E,M,"Up");

    Timestart = MPI_Wtime();
    // LOOPING TEMPERATURES
    for (double T = T_initial; T <= T_final; T+= T_step){
        // Setup for new round
        initialize_new_round(L,Lattice,E,M,"Up");  // could be able to setup way to keep lattice orientation
        vec temp_exp_vals(5,fill::zeros); // Vector for holding temporary expectation values
        vec final_exp_vals(5,fill::zeros); // Vector for holding reduced expectation values
        vec w(17);
        for (int dE = -8; dE <= 8; dE+=4) {
            w[dE+8] = exp(-dE/T);
        }
        mt19937_64 gen(idum+int(T));

        for (int cycles = 0; cycles < MC; cycles++){    // MC CYCLES

            metropolis(L,gen,Lattice,w,E,M);

            //Update expectation values if over MCbeforesample
            if (MCbeforesample<=cycles){
                temp_exp_vals[0] += E; temp_exp_vals[1] += E*E;
                temp_exp_vals[2] += M; temp_exp_vals[3] += M*M; temp_exp_vals[4] += fabs(M);
            }

        }   // MC CYCLES END

        for (int i = 0; i < 5; i++){    // Reducing temp expvals to final exp vals
            MPI_Reduce(&temp_exp_vals[i],&final_exp_vals[i],1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        }

        if (my_rank == 0){
            write_exp_values(T,(MC-MCbeforesample)*numprocs,L,final_exp_vals,ofile,outfile);
            cout << "Written for T " << T << " " <<  (T_final-T)/T_step << " left" << endl;
        }

    }   // LOOP OVER TEMPERATURES END
    
    Timeend = MPI_Wtime();
    if (my_rank == 0){
        cout << "Total time " << double(Timeend-Timestart) << "s on " << numprocs << " cores " << endl;
    }

    if (my_rank == 0){  // Closing file with root
        ofile.close();
        cout << "Rank " << my_rank << " closed " << outfile << endl;
    }

    if (my_rank == 0){
        ofstream runtimeout;
        string timingfile = "Runtimes.txt";
        runtimeout.open(timingfile,std::ios::app);
        runtimeout << outfile << endl;
        runtimeout << "Total time " << double(Timeend-Timestart) << "s on " << numprocs << " cores " << endl;
        runtimeout << endl;
        runtimeout.close();
        
    }

    MPI_Finalize ();
    return 0;
} // MAIN END

void initialize_new_round(int Nspins, imat &Lattice, double &Energy, double &Magnetic,string Fillstyle){
    if (strcmp(Fillstyle.c_str(),"Up") == 0){   // Fill lattice with spin up
        Lattice.ones();
        Magnetic = Lattice.size();
    }
    if (strcmp(Fillstyle.c_str(),"Down") == 0){   // Fill lattice with spin down
        Lattice.ones();
        Lattice = Lattice*-1;
        Magnetic = -1.0*Lattice.size();
    }
    if (strcmp(Fillstyle.c_str(),"Random") == 0){   // Fill lattice with random spin directions
        mat randomLattice(size(Lattice),fill::randu); randomLattice = sign(randomLattice*2-1);
        Lattice = conv_to<imat>::from(randomLattice);
        Magnetic = 0.0;
        for (uword x = 0; x < Nspins; ++x) {
            for (uword y = 0; y < Nspins; ++y){
                Magnetic += Lattice(x,y);
            }
        }
    }
    if (strcmp(Fillstyle.c_str(),"Keep") == 0){     // Keep current lattice
        Magnetic = 0.0;
        for (uword x = 0; x < Nspins; ++x) {
            for (uword y = 0; y < Nspins; ++y){
                Magnetic += Lattice(x,y);
            }
        }
    }

    Energy = 0;
    for (uword i = 0; i< Nspins; i++){
        for (uword j = 0; j< Nspins; j++){
            Energy -= double (Lattice(i,j)*( Lattice(PeriodicBoundary(i, Nspins, 1), j))+Lattice(i, PeriodicBoundary(j, Nspins, 1)));
        }
    }
}   // INITIALIZE NEW ROUND END

vec normalizing_expectations(double const T, double const MC, int const L, vec const Exp_vals){
    double MC_norming = 1.0/double(MC);
    double Spin_norming = 1.0/double(L*L);
    double TT_norming = 1.0/(T*T);
    vec normed_exp(5,fill::zeros);

    double exp_E = Exp_vals(0)*MC_norming;
    double exp_EE = Exp_vals(1)*MC_norming;
    double exp_M = Exp_vals(2)*MC_norming;
    double exp_MM = Exp_vals(3)*MC_norming;
    double exp_absM = Exp_vals(4)*MC_norming;

    double Heat_cap = (exp_EE-exp_E*exp_E)*TT_norming*Spin_norming;
    double Mag_susc = (exp_MM-exp_absM*exp_absM)*TT_norming*Spin_norming;

    normed_exp(0) = exp_E*Spin_norming;
    normed_exp(1) = Heat_cap;
    normed_exp(2) = exp_M*Spin_norming;
    normed_exp(3) = Mag_susc;
    normed_exp(4) = exp_absM*Spin_norming;
    return normed_exp;
}

void write_exp_values(double const T, int const MC,int L, vec Exp_vals, std::ofstream& ofile,string filename){
    vec normed_values = normalizing_expectations(T,MC,L,Exp_vals);

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << T;
    ofile << setw(15) << setprecision(8) << normed_values(0);   // Energy
    ofile << setw(15) << setprecision(8) << normed_values(1);   // Heat cap
    ofile << setw(15) << setprecision(8) << normed_values(2);   // Magnetic
    ofile << setw(15) << setprecision(8) << normed_values(3);   // Susceptibility
    ofile << setw(15) << setprecision(8) << normed_values(4) << endl;   // Abs Magnetic

}   // WRITE EXP VALUES END

int metropolis(uword Nspins,mt19937_64 &gen, imat &Lattice, vec &w, double &E, double &M){
    // Looping over the hole lattice
    int acc_counter = 0;
    for (uword lattis = 0; lattis < Nspins*Nspins; lattis++){
        uword xi = uword(RNG(gen)*Nspins);
        uword yi = uword(RNG(gen)*Nspins);

            // Calculating energy change
        int dE =  2*Lattice(xi,yi)*
        (Lattice(xi,PeriodicBoundary(yi,Nspins,-1))+
         Lattice(PeriodicBoundary(xi,Nspins,-1),yi) +
         Lattice(xi,PeriodicBoundary(yi,Nspins,1)) +
         Lattice(PeriodicBoundary(xi,Nspins,1),yi));
            if (RNG(gen) <= w(dE+8)){ // Accept or not
                Lattice(xi,yi) *= -1;   // flip to new accepted config
                M += double(2*Lattice(xi,yi));
                E += double(dE);
                acc_counter++;
            }   // IF ACCEPT OR NOT END
    }   // END LOOP OVER LATTICE
    return acc_counter;
}   // METROPOLIS END