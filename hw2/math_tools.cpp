#include "math_tools.h"
#include <cmath>
double minmod(double a, double b) {
    if (a * b < 0){
        return 0;
    }
    if (std::abs(a) < std::abs(b)) {
        return a;
    }
    else{
        return b;
    }

}

double centered_diff(double fpos,double f,double fneg, double dx){
    return (fpos - 2*f + fneg) / (std::pow(dx,2)) ;
}

double quadratic_interpolation(Grid2d & grid,std::vector<double> & func,double x, double y){
    if (x < grid.get_xmin())
        x = grid.get_xmin();
    if (x > grid.get_xmax())
        x = grid.get_xmax();
    if (y < grid.get_ymin())
        y = grid.get_ymin();
    if (y > grid.get_ymax())
        y = grid.get_ymax();

    double phi;
    double dx = grid.get_dx();
    double dy = grid.get_dy();
    double cx1;
    double cx2;
    double cy1;
    double cy2;
    int i = floor( (x - grid.get_xmin()) / dx);
    int j = floor( (y - grid.get_ymin()) / dy);

    cx1 = centered_diff(func[grid.n_from_ij(i + 1, j)], func[grid.n_from_ij(i, j)], func[grid.n_from_ij(i - 1, j)], dx);
    cy1 = centered_diff(func[grid.n_from_ij(i, j + 1)], func[grid.n_from_ij(i, j)], func[grid.n_from_ij(i, j - 1)], dy);
    cx2 = centered_diff(func[grid.n_from_ij(i + 2, j)], func[grid.n_from_ij(i + 1, j)], func[grid.n_from_ij(i, j)], dx);
    cy2 = centered_diff(func[grid.n_from_ij(i, j + 2)], func[grid.n_from_ij(i, j + 1)], func[grid.n_from_ij(i, j)], dy);

    double x_i = grid.get_xmin() + i * dx;
    double y_j = grid.get_ymin() + j * dy;
    double x_ip1 = x_i + dx;
    double y_jp1 = y_j + dy;

    phi  = func[grid.n_from_ij(i    ,   j  )]  * ( x_ip1 - x   ) * ( y_jp1 - y   ) / (dx*dy);
    phi += func[grid.n_from_ij(i+1,   j  )] *( x     - x_i ) * ( y_jp1 - y   ) / (dx*dy) ;
    phi += func[grid.n_from_ij(i    , j+1)] *( x_ip1 - x   ) * ( y     - y_j ) / (dx*dy) ;
    phi += func[grid.n_from_ij(i+1, j+1)] *( x     - x_i ) * ( y     - y_j ) / (dx*dy) ;
    phi += - 0.5 * (x- x_i) * (x_ip1 - x) * minmod(cx1, cx2)  - 0.5 * (y - y_j) * (y_jp1 - y) * minmod(cy1, cy2) ;
    return phi;
}