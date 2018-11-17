#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char **argv) {
    // Initialize the random generator
    arma::arma_rng::set_seed_random();

    mat Lattice;
    uword i = 1;
    uword y = 2;
    int add = -1;
    cout << (i+y+add) << endl;
    /*
    // Create a 4x4 random matrix and print it on the screen
    arma::Mat<double> A = arma::randu(4,4);
    std::cout << "A:\n" << A << "\n";
    cout << A.size() << endl;

    // Multiply A with his transpose:
    std::cout << "A * A.t() =\n";
    std::cout << A * A.t() << "\n";

    // Access/Modify rows and columns from the array:
    A.row(0) = A.row(1) + A.row(3);
    A.col(3).zeros();
    std::cout << "add rows 1 and 3, store result in row 0, also fill 4th column with zeros:\n";

    std::cout << "A:\n" << A << "\n";

    // Create a new diagonal matrix using the main diagonal of A:
    arma::Mat<double>B = arma::diagmat(A);
    std::cout << "B:\n" << B << "\n";

    // Save matrices A and B:
    A.save("A_mat.txt", arma::arma_ascii);
    B.save("B_mat.txt", arma::arma_ascii);
    */
    return 0;
}
