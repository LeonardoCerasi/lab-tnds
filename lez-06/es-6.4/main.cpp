#include <iostream>
#include <iomanip>
#include <cmath>

#include "bisection.h"
#include "secant.h"

int main()
{
    int epsilon;
    std::cout << "\nPrecision: 1e-";
    std::cin >> epsilon;
    auto p {[] (double x) -> double {return (3*x*x + 5*x - 2);}};
    bisection b (pow(10, -epsilon));
    secant s (pow(10, -epsilon));

    std::cout << "\nZero between 0 and 1:\n" <<std::endl;
    std::cout << "(bisection)\t" << std::fixed << std::setprecision(-log10(b.get_precision())) << b.find_roots(0, 1, p) << std::endl << std::endl;
    std::cout << "(secant)\t" << std::fixed << std::setprecision(-log10(b.get_precision())) << s.find_roots(0, 1, p) << std::endl << std::endl;

    return 0;
}
