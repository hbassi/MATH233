#ifndef LAB01_MATH_TOOLS_H
#define LAB01_MATH_TOOLS_H

#include "Grid2d.h"
#include <vector>

double quadratic_interpolation(Grid2d & grid,std::vector<double> & func,double x, double y);
double minmod(double a, double b);
double centered_diff(double fxp,double fx,double fxm, double dx);
#endif //LAB01_MATH_TOOLS_H