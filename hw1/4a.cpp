//
// Created by Hardeep on 9/5/2022.
#include <iostream>
//forward declaration
double Legendre(double x, int n);
//power function from page 67 of text book
double power(double num, int pow);
int main ()
{
double x = 0; int n = 0;
std::cout<<"Grid point x to be evaluated: " << std::endl;
std::cin >> x;
std::cout<<"Degree of Legendre polynomial: " <<std::endl;
std::cin >> n;
if (n > 6 || n < 0) {
    std::cout << "Value of n must be 0 <= n <= 6" << std::endl;
    return 0;
    exit(0);
}
else {
    std::cout<<"At x = "<< x << ", Legendre polynomial of degree " << n << " yields: " << Legendre(x, n) <<std::endl;
    return 0;
}

}
double power(double num, int pow) {
    switch(pow) {
        case 0: return 1;
        case 1: return num;
        case 2: return num*num;
        default: {
            double val = num;
            for (int i = 0; i < pow; i++) {
                val *= num;
            }
            return val;
        }
    }
}
double Legendre(double x, int n) {
    if (n == 0) {return 1;}
    else if (n == 1) {return x;}
    else if (n == 2) {return (0.5)* (3*power(x,2) - 1);}
    else if (n == 3) {return (0.5)*(5*power(x,3) - 3*x);}
    else if (n == 4) {return (0.125)* (35*power(x,4) - 30*power(x,2)+3);}
    else if (n == 5) {return (0.125) * (63*power(x,5) - 70* power(x,3) + 15*x);}
    else {return (0.0625) * (231*power(x,6) - 315* power(x,4) + 105* power(x,2) - 5);}
}
//
