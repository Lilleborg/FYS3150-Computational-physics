#include <iostream>
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;


void print(std::vector<double> const &input);
void EnergyCalculation(const mat &Lattice, double &E, uword Nspins);
void MetropolisAlgorithm(uword Nspins, mat &Lattice, int MC, vector<double> &Energy, double T, vector<double> &MagneticMom);

inline uword PeriodicBoundary(uword i, uword limit, uword add) { //Theft
  return (i+limit+add) % (limit);
}

int main()
{
    uword Nspins = 2;
    double T = 1.0 ;
    int MC = 1000;

    vector<double> Energy;
    vector<double> MagneticMom;
    vector<double> SpecificHeat;
    vector<double> Suscpeptibility;

    mat Lattice(Nspins, Nspins, fill::ones); //Initiate lattice

    MetropolisAlgorithm(Nspins, Lattice, MC, Energy, T, MagneticMom);

    //print(Energy);

    return 0;
} // MAIN END

void EnergyCalculation(const mat &Lattice, double &E, uword Nspins)
{
    //Calculate energy of whole lattice
    for (uword i = 0; i<Nspins; i++){
        for (uword j = 0; j<Nspins; j++){
            E -= double (Lattice(i,j)*( Lattice(PeriodicBoundary(i, Nspins, 1), j))
                    + Lattice(i, PeriodicBoundary(j, Nspins, 1)));
        }
    }
}

void MetropolisAlgorithm(uword Nspins, mat &Lattice, int MC, vector<double> &Energy, double T, vector<double> &MagneticMom)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double>RandomGenerator(0.0, 1.0);
    double E0 = 0;
    double E;
    double w;
    double z;
    double delta;
    double TotalEnergy;
    int rejected = 0;
    int accepted = 0;


    EnergyCalculation(Lattice, E0, Nspins);
    TotalEnergy = E0;

    for (int i=0; i<MC; i++){
        E0 = 0.0;
        E = 0.0;
        w = 0.0;
        z = 0.0;

        EnergyCalculation(Lattice, E0, Nspins); //Calculate initial energy
        TotalEnergy += E0;
        cout << E0 << endl;

        //Choose random position in lattice and flip spin
        uword x = uword ((RandomGenerator(gen)*Nspins));
        uword y = uword ((RandomGenerator(gen)*Nspins));
        Lattice(x, y) *= -1;

        cout << Lattice << endl;
        //Calculate new energy

        EnergyCalculation(Lattice, E, Nspins);
        delta = E-E0;
        if (delta <= 0.0){ //Keep energy if new one is lower
            TotalEnergy += E;
            Energy.push_back(double (E));
            MagneticMom.push_back(double (2*Lattice(x,y)));
            accepted++;
        }
        else{ //If energy is larger
            w = exp(-delta/T);
            if (w >= double (RandomGenerator(gen)) ){ //If true, flip spin back again
                rejected++;
                Lattice(x, y) *= -1;
            }
            else{ //Keep energy if not true
                accepted++;
                TotalEnergy += E;
                Energy.push_back( double (E0) );
                MagneticMom.push_back( double (2*Lattice(x,y)) );
                //SpecificHeat.push_back( double 1./T * ())

            }
        }

    }
    cout << TotalEnergy/MC << endl;
}


//USED FOR PRINTING TYPE VECTOR IF NEEDED
void print(std::vector<double> const &input) //Theft
{
    for (uword i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}
