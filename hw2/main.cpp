#include <iostream>
#include "math_tools.h"
#include "Grid2d.h"
#include <vector>
#include <cmath>
#include "SL_method.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

int main(){
    long N = 20;
    long M = 20;
    double xmin = -1.;
    double xmax = 1.;
    double ymin = -1.;
    double ymax = 1.;

    Grid2d newGrid(N, M, xmin, xmax, ymin, ymax);

    double dx = newGrid.get_dx();
    double dy = newGrid.get_dy();
    std::cout << "This is dx: " << newGrid.get_dx() << std::endl;
    std::cout << "This is dy: " << newGrid.get_dy() << std::endl;
    // dx/dt ratio vary base on multiplier (0.5,1,5,10)
    double dt = dx * 1;
    std::cout << "This is dt: " << dt << std::endl;

    SL_method semi_lagrangian = SL_method();
    semi_lagrangian.set_grid(newGrid, N, M);
    semi_lagrangian.method(dt, 2*M_PI);
    std::cout << "SLM done" << std::endl;
    //semi_lagrangian.phi0(semi_lagrangian.get_tsol());
    double err = semi_lagrangian.err();
    std:: cout << err << std::endl;
    return 0;
}