#include "exercises.h"

int exe_b(string filenamestart,uword L, double Temperature){

    vector <double> Exp_E_diffing;  // Holding absdiff of calculated exp_E vs exact_E for different lengths of MCcycles
    vec normed_quantities;          // holding final quantities after norming
    vector <string> quantitynames = {"Exp E", "Heat Cap", "Exp M" , "Susceptibility","Exp Abs M"};
    double T,E,M;    // temperatur, energy and magnetic moment
    int MCsFinal=0;    // updates to hold the number of MCcycles required
    T = Temperature;
    // Exact calculations
    double Z = 2*exp(-8.0/T)+2*exp(8.0/T)+12;   // Partition function for L=2
    double E_exact = -32.0/Z*sinh(8.0/T)/4;     // Exact energy for L=2

    // Seed CHANGE TO DEPEND ON MY_RANK EVENTUALLY
    //random_device rd;
    mt19937_64 gen(1234);
    for (int i = 8; i < 24;i++){ // looping different number of MC cycles
        // Initializing
        int MC = int(pow(2,i));      // current # cycles

        // Arrays
        vec temp_exp_vals(5,fill::zeros); // Vector for holding temporary expectation values
        imat Lattice(L, L, fill::ones);   // imat giving typedef <sword> matrix - armadillos integer type
        double *Energies = new double[MC+1];  // FOR SAVING ENERGIES PER MC CYCLE, ONLY USED WHEN LOOKING AT PATH TO EQUILIBRIUM
        double *MagneticMom = new double[MC+1];   // SAME AS "Energies", but for magnetic moment

        vec w(17);
        for (int dE = -8; dE <= 8; dE+=4) {
            w(dE+8) = exp(-dE/T);
        }

        initialize_new_round(L,Lattice,E,M,"Up");   // Sets up Lattice, calc M and E all spins up, WILL BE MORE USEFULL FOR MULTIPLE TEMPERATURES
        Energies[0] = E;
        MagneticMom[0] = M;
        // STARTING MC CYCLES
        for (int cycle = 0; cycle < MC; cycle ++){

            metropolis(L,gen,Lattice,w,E,M);  // One cycle through the lattice
            Energies[cycle+1] = E;
            MagneticMom[cycle+1] = M;
            // Update expectation values:
            temp_exp_vals(0) += E; temp_exp_vals(1) += E*E;
            temp_exp_vals(2) += M; temp_exp_vals(3) += M*M; temp_exp_vals(4) += fabs(M);

        } // END MC CYCLES
        double exp_E = temp_exp_vals(0)/MC/L/L;
        Exp_E_diffing.push_back(abs(exp_E-E_exact));
        if (Exp_E_diffing.back() < 1e-3){   // calc ~= exact
            cout << "Expectation energy difference " << Exp_E_diffing.back() << " with " << MC << " number of cycles" << endl;
            MCsFinal = MC;
            normed_quantities = normalizing_expectations(T,MCsFinal,L,temp_exp_vals);
        }
    }   // LOOPING OVER I END
    write_double_vector(Exp_E_diffing,"Exp_E_diffing");
    for (int i = 0; i < normed_quantities.size();i++){
        cout << normed_quantities(i) << " : "  << quantitynames[i] << endl;
    }
    cout << "\nexe_b() done" << endl;
    cout << "------------" << endl;
    return 0;
}   // EXE B END

int exe_c(double const Temp, string Latticestart, int const MC){
    double T = Temp,E,M;    // temperatur, energy and magnetic moment
    uword L = 20;
    // Arrays
    vec temp_exp_vals(5,fill::zeros); // Vector for holding temporary expectation values
    imat Lattice(L, L, fill::ones);   // imat giving typedef <sword> matrix - armadillos integer type
    double *Energies = new double[MC+1];  // FOR SAVING ENERGIES PER MC CYCLE, ONLY USED WHEN LOOKING AT PATH TO EQUILIBRIUM
    double *MagneticMom = new double[MC+1];   // SAME AS "Energies", but for magnetic moment

    vec w(17);
    for (int dE = -8; dE <= 8; dE+=4) {
        w(dE+8) = exp(-dE/T);
    }
    initialize_new_round(L,Lattice,E,M,"Up");



}   // EXE C END
