    //
// Created by Matt Blomquist on 9/27/22.
//

#ifndef LAB01_MATH_TOOLS_H
#define LAB01_MATH_TOOLS_H

#include "Grid2d.h"
#include <vector>


double bilinear_interpolation(Grid2d & grid,std::vector<double> & func,double x, double y);
double quadratic_interpolation(Grid2d & grid,std::vector<double> & func,double x, double y);
double minmod(double x, double y);
double centered_diff(double dx, double fpos, double f, double fneg);

#endif //LAB01_MATH_TOOLS_H
