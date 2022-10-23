//
// Created by Matt Blomquist on 9/29/22.
//

#include "SL_method.h"
#include "cmath"
SL_method::SL_method() {}


void SL_method::velocity_field(double x, double y) {
    vf.assign(2,0.0);
    vf[0] = -y;
    vf[1] = x;
}
//\phi(x,y,0)
void SL_method::phi0(std::vector<double> &sol) {
    for (int i = 0; i < xx*yy; i++) {
        sol[i] = sqrt(std::pow((sl_grid.x_from_n(i) - 0.25),2.0)
                + sl_grid.y_from_n(i)*sl_grid.y_from_n(i)) - 0.2;
    }
}

void SL_method::find_trajectory(int n, double &x_d, double &y_d, double dt) {
    double x_0 = sl_grid.x_from_n(n);
    double y_0 = sl_grid.y_from_n(n);
    //modify the velocity vector
    double xast = x_0 - 0.5*dt*(-y_0);
    double yast = y_0 - 0.5*dt*(x_0);
    //velocity_field(xast, yast);
    x_d = x_0 - dt * (-yast);
    y_d = y_0 - dt * xast;
}