#ifndef F22_MATH_233_LABS_SL_METHOD_H
#define F22_MATH_233_LABS_SL_METHOD_H

#include "Grid2d.h"
#include "math_tools.h"
#include <vector>

// Semi-Langrangian Method
class SL_method {
private:
    Grid2d sl_grid;
    std::vector<double> prev_sol;
    std::vector<double> sol;
    int xx;
    int yy;
    void find_trajectory(int n, double & x_d, double & y_d, double dt);
    std::vector<double> G_mat;
    std::vector<double> reinit;

public:
    std::vector<double> true_sol;
    SL_method(); // constructor
    void set_grid(Grid2d &new_grid, int N, int M);; // set grid
    std::vector<double> get_sol(){ return sol; }        // access solution
    void method(double dt, double tf, bool remethod);
    std::vector<double> phi0(std::vector<double> & sol0);
    void godunov();
    void reinit_scheme(double dt, double tf);
};


#endif //F22_MATH_233_LABS_SL_METHOD_H