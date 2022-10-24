//
// Created by Matt Blomquist on 9/29/22.
//

#include "SL_method.h"
#include "cmath"
#include <algorithm>
#include <ntdef.h>

SL_method::SL_method() {}

void SL_method::set_grid(Grid2d & new_grid, double N, double M){
    sl_grid = new_grid;
    xx = N;
    yy = M;
}

void SL_method::velocity_field(double x, double y) {
    vf.assign(2,0.0);
    vf[0] = -y;
    vf[1] = x;
}
//\phi(x,y,0)
void SL_method::phi0(std::vector<double> sol) {
    sol.assign(xx * yy, 0.0);
    for (int i = 0; i < xx * yy; i++) {
        sol[i] = sqrt((sl_grid.x_from_n(i) - 0.25) * (sl_grid.x_from_n(i) - 0.25)
                + sl_grid.y_from_n(i)*sl_grid.y_from_n(i)) - 0.2;
    }
}

void SL_method::find_trajectory(int n, double &x_d, double &y_d, double dt) {
    double x_0 = sl_grid.x_from_n(n);
    double y_0 = sl_grid.y_from_n(n);
    //modify the velocity vector
    velocity_field(x_0,y_0);
    double xast = x_0 - 0.5*dt*vf[0];
    double yast = y_0 - 0.5*dt*vf[1];
    velocity_field(xast, yast);
    x_d = x_0 - dt * vf[0];
    y_d = y_0 - dt * vf[1];
}

void SL_method::method(double tf, double dt){
    sol.assign(xx * yy, 0.0);
    prev_sol.assign(xx * yy, 0.0);
    std::vector<double> xd;
    std::vector<double> yd;
    xd.assign(xx * yy, 0.0);
    yd.assign(xx * yy, 0.0);

    for (int i =0; i < xx; i++) {
        for (int j = 0; j < yy; j++) {
            find_trajectory(i + j * yy, xd[i + j * yy], yd[i + j * yy], dt);
        }
    }
    phi0(prev_sol);
    for (int i = 0; i < ceil(tf / dt); i++) {
        for (int j = 0; j < xx; j++) {
            for (int k = 0; k < yy; k++) {
                sol[j + k * yy] = quadratic_interpolation(sl_grid, prev_sol, xd[j + k * yy], yd[j + k * yy]);
            }
        }
        prev_sol = sol;
    }
}

double SL_method::err() {
    double err = 0.0;
    phi0(true_sol);
    for (int i = 0; i < xx * yy; i++)
        err = std::max(std::abs(sol[i] - true_sol[i]), err);
    return err;
}