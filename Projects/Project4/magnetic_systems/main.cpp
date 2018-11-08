#include <iostream>
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;


void print(std::vector<double> const &input);
void Initialize(mat &Lattice, int Nspins);
void EnergyCalculation(mat &Lattice, double &E, int Nspins);
void MetropolisAlgorithm(int Nspins, mat &Lattice, int MC, vector<double> &Energy, double T, vector<double> &MagneticMom);

inline int PeriodicBoundary(int i, int limit, int add) { //Theft
  return (i+limit+add) % (limit);
}

int main()
{
    int Nspins = 2;
    double T = 1.0 ;
    int MC = 1000;
    vector<double> Energy;
    vector<double> MagneticMom;
    mat Lattice(Nspins, Nspins, fill::zeros);

    MetropolisAlgorithm(Nspins, Lattice, MC, Energy, T, MagneticMom);

    /*
    cout << "Energy = " << endl;
    print(Energy);
    cout << " " << endl;
    cout << "Magnetic Moment = " << endl;
    print(MagneticMom);
    cout << " " << endl;
    */

    int sum_of_elems = 0;
    std::for_each(Energy.begin(), Energy.end(), [&] (int n) {
        sum_of_elems += n;
    });
    cout << (double)sum_of_elems/(double) MC << endl;
    return 0;
}

void Initialize(mat &Lattice, int Nspins)
{
    //Fill initial matrix and initial magnetic moment
    for (int i = 0; i<Nspins; i++){
        for (int j = 0; j<Nspins; j++){
            Lattice(i,j) = 1.0; //Spin up for ground state
        }
    }
}
void EnergyCalculation(mat &Lattice, double &E, int Nspins)
{
    //Calculate energy of whole lattice
    for (int i = 0; i<Nspins; i++){
        for (int j = 0; j<Nspins; j++){
            E -= (double) Lattice(i,j)*( Lattice(PeriodicBoundary(i, Nspins, -1), j))
                    + Lattice(i, PeriodicBoundary(j, Nspins, -1));
        }
    }
}

void MetropolisAlgorithm(int Nspins, mat &Lattice, int MC, vector<double> &Energy, double T, vector<double> &MagneticMom)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double>RandomGenerator(0.0, 1.0);
    double E0 = 0;
    double E = 0;
    double w = 0;

    Initialize(Lattice, Nspins); //Initialize lattice
    //cout << Lattice << endl;

    for (int i=0; i<MC; i++){
        E0 = 0.0;
        E = 0.0;
        w = 0.0;
        //cout << i << endl;
        EnergyCalculation(Lattice, E0, Nspins); //Calculate initial energy
        cout << E0 << endl;
        //Choose random position in lattice and flip spin
        int x = (int) (RandomGenerator(gen)*Nspins);
        int y = (int) (RandomGenerator(gen)*Nspins);
        Lattice(x, y) *= -1;
        cout << Lattice << endl;
        //Calculate new energy
        E = E0;
        EnergyCalculation(Lattice, E, Nspins);
        if (E-E0 < 0.0){ //Keep energy if new one is lower
            Energy.push_back((double) E0);
            MagneticMom.push_back((double) 2*Lattice(x,y));
        }
        else{ //If energy is larger
            w = exp(-1*(E-E0)/T);
            if (w >= (double) RandomGenerator(gen)){ //If true, flip spin back again
                Lattice(x, y) *= -1;
            }
            else{ //Keep energy if not true
                Energy.push_back((double) E0);
                MagneticMom.push_back((double) 2*Lattice(x,y));
            }
        }

    }
}

void print(std::vector<double> const &input) //Theft
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}
