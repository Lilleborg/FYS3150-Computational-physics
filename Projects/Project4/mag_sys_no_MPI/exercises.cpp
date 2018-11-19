#include "exercises.h"

int exe_b(uword L, double Temperature){
    cout << "Starting exe_b() for T " << Temperature << endl;

    vector <double> Exp_E_diffing;  // Holding absdiff of calculated exp_E vs exact_E for different lengths of MCcycles
    vector <double> Exp_absM_diffing;
    vec normed_quantities;          // holding final quantities after norming
    vector <string> quantitynames = {"Exp E", "Heat Cap", "Exp M" , "Susceptibility","Exp Abs M"};
    double T,E,M;    // temperatur, energy and magnetic moment
    T = Temperature;
    // Exact calculations
    double Z = 2*exp(-8.0/T)+2*exp(8.0/T)+12;   // Partition function for L=2
    double E_exact = -32.0/Z*sinh(8.0/T)/4;     // Exact energy for L=2
    double absM_exact = 1.0/Z*(8.0*exp(8)+16)/4;

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
            w[dE+8] = exp(-dE/T);
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
            temp_exp_vals[0] += E; temp_exp_vals[1] += E*E;
            temp_exp_vals[2] += M; temp_exp_vals[3] += M*M; temp_exp_vals[4] += fabs(M);

        } // END MC CYCLES
        double exp_E = temp_exp_vals[0]/MC/L/L;
        double exp_absM = temp_exp_vals[4]/MC/L/L;
        Exp_E_diffing.push_back(abs(exp_E-E_exact)/abs(E_exact));
        Exp_absM_diffing.push_back(abs(exp_absM-absM_exact)/absM_exact);
        if (Exp_E_diffing.back() < 1e-3){   // calc ~= exact
            cout << "Relative error expectation energy " << Exp_E_diffing.back() << " with " << MC << " number of cycles" << endl;
            normed_quantities = normalizing_expectations(T,MC,L,temp_exp_vals);
        }
        if(i==23){
            write_double_array_bin(Energies,MC,"/ExerciseB/Energies");
        }
    }   // LOOPING OVER I END
    write_double_vector(Exp_E_diffing,"/ExerciseB/Exp_E_diffing");
    write_double_vector(Exp_absM_diffing,"/ExerciseB/Exp_absM_diffing");
    for (int i = 0; i < normed_quantities.size();i++){
        cout << normed_quantities(i) << " : "  << quantitynames[i] << endl;
    }
    cout << "\nexe_b() done" << endl;
    cout << "------------" << endl;
    return 0;
}   // EXE B END

int exe_c(double const Temp, string Latticestart, int const MC){

    double T = Temp,E,M;    // temperatur, energy and magnetic moment
    cout << "Starting exe_c() for T " << T << " " << Latticestart << endl;
    uword L = 20;           // Nr spins along one axis
    double norming = 1.0/(double(L*L)); // 1.0/(double(MC))
    mt19937_64 gen(1234);
    // Arrays
    //vec temp_exp_vals(5,fill::zeros); // Vector for holding temporary expectation values
    imat Lattice(L, L);   // imat giving typedef <sword> matrix - armadillos integer type
    double *Energies = new double[MC+1];  // FOR SAVING ENERGIES
    double *Magnetic = new double[MC+1];   // SAME AS "Energies", but for magnetic moment
    double *EnergyPerCycle = new double[MC+1];
    double *MagneticPerCycle = new double[MC+1];
    double *Accept_Counter = new double[MC+1];

    vec w(17);
    for (int dE = -8; dE <= 8; dE+=4) {
        w[dE+8] = exp(-dE/T);
    }
    // Starting values
    initialize_new_round(L,Lattice,E,M,Latticestart);
    Energies[0] = E*norming;
    Magnetic[0] = M*norming;
    EnergyPerCycle[0] = Energies[0];
    MagneticPerCycle[0] = Magnetic[0];
    // STARTING MC CYCLES
    int counter = 0;

    for (int cycle = 0; cycle < MC; cycle ++){

        Accept_Counter[cycle] =  metropolis(L,gen,Lattice,w,E,M);  // One cycle through the lattice
        counter++;
        Energies[cycle+1] = (Energies[cycle]+E*norming);
        Magnetic[cycle+1] = Magnetic[cycle] + fabs(M)*norming;
        EnergyPerCycle[cycle+1] = Energies[cycle+1]/counter;
        MagneticPerCycle[cycle+1] = Magnetic[cycle+1]/counter;

    }   // END MC CYCLES

    // WRITING TO FILE
    string filenames = "ExerciseC/"+Latticestart+"_T_";
    filenames.append(to_string(T));
    write_double_array_bin(Energies,MC,filenames + "Energies_");
    write_double_array_bin(Magnetic,MC,filenames + "AbsMagnetic_");
    write_double_array_bin(EnergyPerCycle,MC,filenames + "Energy_per_mc_");
    write_double_array_bin(MagneticPerCycle,MC,filenames + "Magnetic_per_mc_");
    write_double_array_bin(Accept_Counter,MC,filenames + "Accept_per_mc_");

    delete [] Energies;
    delete [] Magnetic;
    delete [] EnergyPerCycle;
    delete [] MagneticPerCycle;
    delete [] Accept_Counter;

    cout << "\nexe_c() done for T " << T << " " << Latticestart << endl;
    cout << "------------" << endl;
    return 0;
}   // EXE C END

int exe_d(double const Temp, string Latticestart, int const MC){

    // Initializing
    double T = Temp ,E,M;    // temperatur, energy and magnetic moment
    cout << "Starting exe_d() for T " << T << " " << Latticestart << endl;
    int MCbeforesample = 1e3;
    if (T > 1.1){
        MCbeforesample = 1e4;
    }
    uword L = 20;           // Nr spins along one axis

    mt19937_64 gen(1234);
    imat Lattice(L, L);   // imat giving typedef <sword> matrix - armadillos integer type

    double *Energies = new double[MC-MCbeforesample];
    vec temp_exp_vals(2,fill::zeros); // Vector for holding temporary expectation values
    // Set up possible energy differences
    vec w(17);
    for (int dE = -8; dE <= 8; dE+=4) {
        w(dE+8) = exp(-dE/T);
    }
    // Computing
    initialize_new_round(L,Lattice,E,M,Latticestart);

    for (int cycle = 0; cycle < MC; ++cycle) {
        metropolis(L,gen,Lattice,w,E,M);
        if (MCbeforesample<=cycle){
            Energies[cycle-MCbeforesample] = E;
            temp_exp_vals(0) += E;
            temp_exp_vals(1) += E*E;
        }
    }

    // Writing to file
    string filename = "ExerciseD/"+Latticestart+"_T_"+to_string(T)+"_Energy_levels_";
    write_double_array_bin(Energies,MC-MCbeforesample,filename);

    double variance = find_variance(temp_exp_vals(1),temp_exp_vals(0), MC-MCbeforesample);
    cout << "Variance Energy " << variance << " for " << MC-MCbeforesample << " sampling points" << endl;

    delete [] Energies;
    cout << "\nexe_d() done for T " << T << " " << Latticestart << endl;
    cout << "------------" << endl;
    return 0;
}   // EXE D END

int exe_e(string Latticestart, int const MC){
    cout << "Starting exe_E() " << Latticestart << " MC " << MC << endl;
    ofstream ofile;
    int MCbeforesample = 1e4;
    for (uword L = 40; L<50; L+=20){ //CHANGE TO L<101 LATER
        string filenames = "../datafiles_no_MPI/ExerciseE/"+Latticestart+"_L_"+to_string(L) + ".txt";
        ofile.open(filenames);  // Open file for this L
        for (double T = 2.1; T<2.35; T+=0.005){

            cout << "Starting exe_E() for L = " << L << " " << Latticestart << " T " << T << endl;
            double E,M;    // temperatur, energy and magnetic moment
            mt19937_64 gen(1+T+L);

            // Arrays
            vec temp_exp_vals(5,fill::zeros); // Vector for holding temporary expectation values
            imat Lattice(L, L);   // imat giving typedef <sword> matrix - armadillos integer type

            vec w(17);
            for (int dE = -8; dE <= 8; dE+=4) {
                w[dE+8] = exp(-dE/T);
            }
            // Starting values
            initialize_new_round(L,Lattice,E,M,Latticestart);

            // STARTING MC CYCLES

            for (int cycle = 0; cycle < MC; cycle ++){
                metropolis(L,gen,Lattice,w,E,M);

                // Update expectation values if equilibrium
                if (MCbeforesample<=cycle){
                    temp_exp_vals[0] += E; temp_exp_vals[1] += E*E;
                    temp_exp_vals[2] += M; temp_exp_vals[3] += M*M; temp_exp_vals[4] += fabs(M);
                }
            }   // END MC CYCLES
            // WRITING TO FILE
            write_exp_values(T,MC-MCbeforesample,L,temp_exp_vals,ofile,filenames);

            cout << "Done for L = " << L << " " << Latticestart << " " << T << endl;
            cout << "------------" << endl;

        }   // LOOP OVER T END
        ofile.close();
        cout << "Closed " << filenames << endl;
    }   // LOOP OVER L END
    cout << "\nexe_e() done" << endl;
    cout << "------------" << endl;
    return 0;
}   // EXE E END
