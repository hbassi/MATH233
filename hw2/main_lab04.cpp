//
// Created by Matt Blomquist on 10/13/22.
//

#include <iostream>

#include "Matrix.h"

int main() {
    std::cout << "Hello, MATH233 Lab 04" << std::endl;
    // declare sparse matrix
    SparseMatrix_CRS A;
    // add values to A
    A.add_element(0, 1, 25.);
    A.add_element(2, 2, 30.);
    A.add_element(2, 3, 30.);
    A.add_element(2, 3, 30.);
    A.add_element(2, 2, 30.);

    A.print();
    std::cout << "Print A in full:" << std::endl;
    A.print_As_Full();

    std::vector<double> x;
    x.assign(2,0.);




    return 0;
}