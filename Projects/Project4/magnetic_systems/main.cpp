#include <iostream>
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

// DECLARE FUNCTIONS
void write_double_vector(vector<double> const input, string filename, string path = "./txtfiles/");

void initialize_new_round(uword Nspins, imat& Lattice, double &Energy, double &MagneticMom);
void metropolis(uword Nspins, int MCs, double T,__1::mt19937_64 gen, imat &Lattice, vec &w, double &E, double &M);
void results_per_mc(double *quantity,int MC, string filename);

inline uword PeriodicBoundary(uword i, uword limit, int add) { //Theft
    return (i+limit+add) % (limit);
}

int main()
{
    uword Nspins = 2;
    double T,E,M;    // temperatur, energy and magnetic moment
    T = 3.;
    int MC = 1e5;      // # cycles
    double norm = 1.0/double(MC);
    double totspins = Nspins*Nspins;

    vec ExpectationVals(5,fill::zeros); // Vector for holding expectation values
    // Initialize lattice matrix,
    imat Lattice(Nspins, Nspins, fill::ones);   // imat giving typedef <sword> matrix - armadillos integer type
    double *Energies = new double[MC+1];  // FOR SAVING ENERGIES PER MC CYCLE, ONLY USED WHEN LOOKING AT PATH TO EQUILIBRIUM
    double *MagneticMom = new double[MC+1];   // SAME AS "Energies", but for magnetic moment


    // Initialize seed CHANGE TO DEPEND ON MY_RANK EVENTUALLY
    random_device rd;
    cout << time(0)<< endl;
    mt19937_64 gen(uword(time(0)));

    // FROM HERE WE SHOULD LOOP OVER TEMPERATURES EVENTUALLY
    // Precalculating possible energy differences, fill vector of probability ratios
    vec w(17);

    for (int dE = -8; dE <= 8; dE+=4) {
        w(dE+8) = exp(-dE/T);
    }

    /*
    vec w(5,fill::zeros), dE = linspace(-8,8,5);
    for (uword i = 0; i < dE.size(); ++i) {
        w(i) = exp(-dE(i)/T);
    }*/
    initialize_new_round(Nspins,Lattice,E,M);   // Sets up Lattice, calc M and E all spins up, WILL BE MORE USEFULL FOR MULTIPLE TEMPERATURES
    Energies[0] = E;
    MagneticMom[0] = M*norm/totspins;

    // STARTING MC CYCLES
    for (int cycle = 0; cycle < MC; cycle ++){

        metropolis(Nspins,MC,T,gen,Lattice,w,E,M);  // One cycle through the lattice
        Energies[cycle+1] = E;
        MagneticMom[cycle+1] = M*norm/totspins;
        // Update expectation values:
        ExpectationVals(0) += E; ExpectationVals(1) += E*E;
        ExpectationVals(2) += M; ExpectationVals(3) += M*M; ExpectationVals(4) += fabs(M);

    }   // END MC CYCLES
    cout << w << endl;
    cout << "Atotal average energy " << ExpectationVals(0)*norm << endl;
    // WRITE TO FILES
    string fileending = "energies_" + to_string(T) + ".bin";
    results_per_mc(Energies,MC,"energies_"+fileending);
    results_per_mc(MagneticMom,MC,"magnetic_"+fileending);

    //write_double_vector(Energy,string ("energy_temp.txt"));
    return 0;
} // MAIN END

void results_per_mc(double *quantity,int MC, string filename){
    cout << "Writing " << filename << endl;
    ofstream file(filename, ofstream::binary);
    file.write(reinterpret_cast<const char*> (quantity), MC*sizeof(double));
    file.close();
    cout << filename << " closed" << endl;
}

void metropolis(uword Nspins, int MCs, double T,__1::mt19937_64 gen, imat &Lattice, vec &w, double &E, double &M){

    // Set up the uniform distribution for x \in [[0, 1]
    uniform_real_distribution<double> RNG(0.0,1.0);
    // Looping over the hole lattice
    for (uword x = 0; x < Nspins; x++){
        for (uword y = 0; y < Nspins; y++){
            uword xi = uword(RNG(gen)*Nspins);
            uword yi = uword(RNG(gen)*Nspins);
            // Energy from spinn (xi,yi)
            //cout << xi << " " << yi << endl;
            //cout << Lattice << endl;
            int dE =  2*Lattice(xi,yi)*
                    (Lattice(xi,PeriodicBoundary(yi,Nspins,-1))+
                     Lattice(PeriodicBoundary(xi,Nspins,-1),yi) +
                     Lattice(xi,PeriodicBoundary(yi,Nspins,1)) +
                     Lattice(PeriodicBoundary(xi,Nspins,1),yi));
            //cout << dE << endl;

            //cout << RNG(gen) << " " << w(dE+8) << endl;
//            cout << "Energy "<< dE << endl;
//            cout << "Prop ratio " << w(dE+8) << endl;
//            cout << "Random nr " << RNG(gen) << endl;

            //RNG(gen
            // rand()/(RAND_MAX*1.0)
            if (RNG(gen) <= w(dE+8)){ // Accept or not
                //cout << "Sampling" << endl;
                Lattice(xi,yi) *= -1;   // flip to new accepted config
                M += double(2*Lattice(xi,yi));
                //cout << "E before " << E << endl;
                //cout << "dE " << dE << endl;
                E += double(dE);
                //cout << "E after " << E << endl;
            }
        }
    }   // END X-DIRECTION, CONCLUDING LOP OVER LATTICE
}   // METROPOLIS END

void initialize_new_round(uword Nspins, imat &Lattice, double &Energy, double &MagneticMom){
    Lattice.ones();
    MagneticMom = Lattice.size();

    Energy = 0;
    for (uword i = 0; i< Nspins; i++){
        for (uword j = 0; j< Nspins; j++){
            Energy -= double (Lattice(i,j)*( Lattice(PeriodicBoundary(i, Nspins, 1), j)) + Lattice(i, PeriodicBoundary(j, Nspins, 1)));
        }
    }
}   // INITIALIZE NEW ROUND END

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
