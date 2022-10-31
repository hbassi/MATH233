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

void SL_method::method(double dt, double tf, bool remethod) {
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
    for (int i = 0; i < floor(tf / dt); i++) {
        for (int j = 0; j < xx; j++){
            for (int k = 0; k < yy; k++) {
                sol[j + k * yy] = quadratic_interpolation(sl_grid, temp, xd[j + k * yy], yd[j + k * yy]);
            }
        }
        //reinit scheme, inside here do godunov(should return the G matrix/vector from paper)
        if (remethod) {
            reinit_scheme(sl_grid.get_dx() / 10.0, tf);
        }
        temp = sol;

    }
}

//https://reader.elsevier.com/reader/sd/pii/S0021999184711557?token=82C69EF077E6C61D6BB8A5D6909A23DE5A9D62269C483B6FD68943B18B76D9CF8C20566E14AAFF03C58B90714FD0C762&originRegion=us-east-1&originCreation=20221025191659
//page 8 of this paper, linked by Matt
void SL_method::godunov(){
    G_mat.assign(xx*yy,0.0);
    for (int i = 0; i < xx; i++) {
        for (int j = 0; j < yy; j++) {
            double a, b, c, d;
            if (i == 0) {
                a = 0.0;
            }
            else {
                a = (reinit[sl_grid.n_from_ij(i, j)] - reinit[sl_grid.n_from_ij(i - 1, j)])/ sl_grid.get_dx();
            }
            if (i == xx - 1) {
                b = 0.0;
            }
            else {
                b = (reinit[sl_grid.n_from_ij(i + 1, j)] - reinit[sl_grid.n_from_ij(i, j)])/ sl_grid.get_dx();
            }
            if (j == 0) {
                c = 0.0;
            } else {
                c = (reinit[sl_grid.n_from_ij(i, j)] - reinit[sl_grid.n_from_ij(i, j - 1)])/ sl_grid.get_dy();
            }
            if (j == yy - 1) {
                d = 0.0;
            }
            else {
                d = (reinit[sl_grid.n_from_ij(i, j + 1)] - reinit[sl_grid.n_from_ij(i, j)])/ sl_grid.get_dy();
            }

            //fill G here [G[n from ij]] needs to be just phi0
            if (sol[sl_grid.n_from_ij(i , j)] > 0.0) {
                double aplus = std::max(a, 0.0);
                double bminus = std::min(b,0.0);
                double cplus = std::max(c,0.0);
                double dminus = std::min(d,0.0);
                G_mat[sl_grid.n_from_ij(i , j)] = std::sqrt(std::max(std::pow(aplus,2.0), std::pow(bminus,2.0))
                                                            + std::max(std::pow(cplus,2.0), std::pow(dminus,2.0))) - 1.0;
            }
            else if (sol[sl_grid.n_from_ij(i , j)] < 0.0){
                double aminus = std::min(a, 0.0);
                double bplus = std::max(b,0.0);
                double cminus = std::min(c,0.0);
                double dplus = std::max(d,0.0);
                G_mat[sl_grid.n_from_ij(i , j)] = std::sqrt(std::max(std::pow(aminus,2.0), std::pow(bplus,2.0))
                                                            + std::max(std::pow(cminus,2.0), std::pow(dplus,2.0))) - 1.0;
            } else {
                G_mat[sl_grid.n_from_ij(i, j)] = 0.0;
            }

        }
    }

}
void SL_method::reinit_scheme(double dt, double tf) {
    std::vector<double> S;
    S.assign(xx * yy, 0.0);
    for (int i = 0; i < xx; i++) {
        for (int j = 0; j < yy; j++) {
            S[sl_grid.n_from_ij(i,j)] = sol[sl_grid.n_from_ij(i , j)]/std::sqrt(std::pow(sol[sl_grid.n_from_ij(i , j)],2.0) + std::pow(sl_grid.get_dx(),2.0));
        }
    }
    reinit = sol;
    //time can be changed (how many iterations)
    for (int t = 0; t < 10; t++) {
        godunov();
        for (int i = 0; i < xx; i++) {
            for (int j = 0; j < yy; j++) {
                reinit[sl_grid.n_from_ij(i, j)] -= dt* S[sl_grid.n_from_ij(i, j)]*G_mat[sl_grid.n_from_ij(i, j)];
            }
        }
        sol = reinit;
    }
}


