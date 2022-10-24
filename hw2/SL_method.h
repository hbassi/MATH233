//
// Created by Matt Blomquist on 9/29/22.
//

#ifndef F22_MATH_233_LABS_SL_METHOD_H
#define F22_MATH_233_LABS_SL_METHOD_H

#include "Grid2d.h"
#include <vector>
#include "math_tools.h"
// Semi-Langrangian Method
class SL_method {
private:
    Grid2d sl_grid;
    std::vector<double> sol;
    std::vector<double> prev_sol;
    std::vector<double> true_sol;
    std::vector<double> vf;
    int xx;
    int yy;
    void find_trajectory(int n, double & x_d, double & y_d, double dt);

public:
    SL_method();
    void set_grid(Grid2d & new_grid, double N, double M); // set grid
    std::vector<double> get_sol(){ return sol; }// access solution
    std::vector<double> get_tsol() {return true_sol;}
    //void set_velocity(std::vector<double> & vel_u0, std::vector<double> & vel_v0);
    void velocity_field(double x, double y);
    void phi0(std::vector<double> sol);

    void method(double tf, double dt);

    double err();
};


#endif //F22_MATH_233_LABS_SL_METHOD_H
