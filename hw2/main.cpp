#include <iostream>
#include "math_tools.h"
#include "Grid2d.h"
#include <vector>
#include <cmath>
#include "SL_method.h"
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
    // dx/dt ratio vary base on multiplier (0.5,1,5,10)
    double dt = max(dx,dy) * 1;

    SL_method semi_lagrangian = SL_method();
    return 0;
}