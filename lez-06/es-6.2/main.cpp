#include <iostream>
#include <iomanip>
#include <cmath>

#include "functions.h"
#include "bisection.h"

int main()
{
    parabola p (3, 5, -2);
    bisection b;
    
    std::cout << "Zero between 0 and 1: ";
    std::cout << std::fixed << std::setprecision(-log10(b.get_precision())) << b.find_roots(0, 1, p) << std::endl;

    return 0;
}
