#include "SL_method.h"
#include "cmath"

using namespace std;

SL_method::SL_method(){

}

//do we need to store anything in a velocity array like in the lab vel_u etc?

void SL_method::set_grid(Grid2d & new_grid, int N, int M){
    sl_grid = new_grid;
    xx = N;
    yy = M;
}

//\phi(x,y,0)
std::vector<double> SL_method::phi0(std::vector<double> & sol){
    //need this or else segmentation fault https://www.geeksforgeeks.org/segmentation-fault-sigsegv-vs-bus-error-sigbus/#:~:text=1)%20Segmentation%20Fault%20(also%20known,doesn't%20have%20access%20to.
    sol.assign(xx * yy, 0.0);
    for (int i = 0; i < xx * yy; i++){
        sol[i] = std::sqrt(std::pow((sl_grid.x_from_n(i) - 0.25),2.0) + std::pow(sl_grid.y_from_n(i),2.0)) - 0.2;
    }
    return sol;
}

void SL_method::find_trajectory(int n, double &x_d, double &y_d, double dt) {
    double x_0 = sl_grid.x_from_n(n);
    double y_0 = sl_grid.y_from_n(n);
    double xast = x_0 - 0.5 * dt * -y_0;
    double yast = y_0 - 0.5 * dt * x_0;
    x_d = x_0 - dt * -yast;
    y_d = y_0 - dt * xast;
}

void SL_method::method(double dt, double tf) {
    sol.assign(xx * yy, 0.0);
    prev_sol.assign(xx * yy, 0.0);
    std::vector<double> xd;
    std::vector<double> yd;
    xd.assign(xx * yy, 0.0);
    yd.assign(xx * yy, 0.0);
    for (int i = 0; i < xx ; i++) {
        for (int j = 0; j < yy; j++) {
            find_trajectory(i + j * yy, xd[i + j * yy], yd[i + j * yy], dt);
         }
    }
    std::vector<double> temp = phi0(prev_sol);
    for (int i = 0; i < ceil(tf / dt); i++) {
        for (int j = 0; j < xx; j++){
            for (int k = 0; k < yy; k++) {
                sol[j + k * yy] = quadratic_interpolation(sl_grid, temp, xd[j + k * yy], yd[j + k * yy]);
            }
        }
        temp = sol;
    }
}



