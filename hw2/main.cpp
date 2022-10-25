#include <iostream>
#include "math_tools.h"
#include "Grid2d.h"
#include <vector>
#include <cmath>
#include "SL_method.h"

using namespace std;

int main(){
    long N = 100;
    long M = 100;

    double xmin = -1.;
    double xmax = 1.;
    double ymin = -1.;
    double ymax = 1.;

    Grid2d newGrid(N, M, xmin, xmax, ymin, ymax);

    double dx = newGrid.get_dx();
    std::cout << "This is dx: " << dx << std::endl;
    //vary dt by multiples of dx (0.5,1,5,10)
    double dt = dx * 10;
    std::cout << "This is dt: " << dt << std::endl;
    SL_method semi_lagrangian = SL_method();
    semi_lagrangian.set_grid(newGrid, N, M);
    semi_lagrangian.method(dt,2 * M_PI);
    std::vector<double> true_sol = semi_lagrangian.phi0(semi_lagrangian.true_sol);
    std::vector<double> sol = semi_lagrangian.get_sol();
    double error = 0.0;
    for (int i = 0; i < N * M; i++) {
        error = std::max(std::abs(sol[i] - true_sol[i]), error);
    }
    std:: cout << error << std::endl;
    return 0;
}

