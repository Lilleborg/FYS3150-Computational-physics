#include "functions.h"

inline uword PeriodicBoundary(uword i, uword limit, int add) { //Theft
    return (i+limit+add) % (limit);
}

// Set up the uniform distribution for x in [0, 1]
uniform_real_distribution<double> RNG(0.0,1.0);

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
            }
    }   // END LOOP OVER LATTICE
    return acc_counter;

}   // METROPOLIS END


void initialize_new_round(uword Nspins, imat &Lattice, double &Energy, double &MagneticMom,string Fillstyle){
    if (strcmp(Fillstyle.c_str(),"Up") == 0){   // Fill lattice with spin up
        Lattice.ones();
        MagneticMom = Lattice.size();
    }
    if (strcmp(Fillstyle.c_str(),"Down") == 0){   // Fill lattice with spin down
        Lattice.ones();
        Lattice = Lattice*-1;
        MagneticMom = -1.0*Lattice.size();
    }
    if (strcmp(Fillstyle.c_str(),"Random") == 0){   // Fill lattice with random spin directions
        mat randomLattice(size(Lattice),fill::randu); randomLattice = sign(randomLattice*2-1);
        Lattice = conv_to<imat>::from(randomLattice);
        MagneticMom = 0.0;
        for (uword x = 0; x < Nspins; ++x) {
            for (uword y = 0; y < Nspins; ++y){
                MagneticMom += Lattice(x,y);
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


// WRITE TO FILE FUNCTIONS-------------------------
void write_double_vector(vector<double> quantity,string filenamestart){
    string filename = filenamestart + "_" + to_string(quantity.size()) +"_elements.dat";
    filename.insert(0,"../datafiles/");
    cout << "Writing " << filename << endl;
    ofstream file(filename);
    for (const auto &e : quantity) file << e << "\n";
    file.close();
}
void write_double_array_bin(double *quantity,int MC, string filename){
    filename.insert(0,"../datafiles/");
    filename.append(to_string(MC));
    filename.append(".bin");
    cout << "Writing " << filename << endl;
    ofstream file(filename, ofstream::binary);
    file.write(reinterpret_cast<const char*> (quantity), MC*sizeof(double));
    file.close();
    cout << filename << " closed" << endl;
}   // RESULTS PER MC END

double find_variance(double qq,double q,int const Norming){
    qq /= Norming;
    double qnormed = q/Norming;
    return qq-qnormed*qnormed;
}   // FIND VARIANCE END

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
    double Mag_susc = (exp_MM-exp_M*exp_M)*TT_norming*Spin_norming;

    normed_exp(0) = exp_E*Spin_norming;
    normed_exp(1) = Heat_cap;
    normed_exp(2) = exp_M*Spin_norming;
    normed_exp(3) = Mag_susc;
    normed_exp(4) = exp_absM*Spin_norming;
    return normed_exp;
}

// TODO: CHANGE HOW FILENAME GETS DEFINED, SHOULD BE ALL DONE OUTSIDE FUNCTION
void write_exp_values(double const T, int const MC,int L, vec Exp_vals, std::ofstream& ofile,string filename){
    cout << "OBS, Remember:\n Write_to_exp_values function takes the UN-NORMED expectation values as argument!" << endl;
    filename.insert(0,"../datafiles/");
    vec normed_values = normalizing_expectations(T,MC,L,Exp_vals);
    cout << "\nWriting expectation values to "<< filename << " for temperature " << T << endl;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << T;
    ofile << setw(15) << setprecision(8) << normed_values(0);   // Energy
    ofile << setw(15) << setprecision(8) << normed_values(1);   // Heat cap
    ofile << setw(15) << setprecision(8) << normed_values(2);   // Magnetic
    ofile << setw(15) << setprecision(8) << normed_values(3);   // Susceptibility
    ofile << setw(15) << setprecision(8) << normed_values(4) << endl;   // Abs Magnetic
    cout << "---------------" << endl;
    cout << "written for temp " << T << " , file not closed yet" << endl;
    cout << "---------------\n" << endl;
}   // WRITE EXP VALUES END



// ----------------------------------------
// BELOW FUNCTIONS ARE NOT CURRENTLY IN USE
// ----------------------------------------
/*
void write_exp_values(vec const input, string filename, string path){
    ofstream ofile(path + filename);
    cout << "Writing file " << filename << endl;

    for (const auto &e : input) ofile << e << "\n";
    cout << "Written" << endl;

}   // WRITE_EXP_VALUES END

//USED FOR PRINTING TYPE VECTOR IF NEEDED
void print(std::vector<double> const &input) //Theft
{
    for (uword i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
    cout << endl;
}
*/
