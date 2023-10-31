#include <iostream>
#include <iomanip>
#include <cmath>

#include "functions.h"
#include "bisection.h"
#include "secant.h"
#include "assert.h"

int main(int argc, char** argv)
{
    test::test_bisection();

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <precision>" << std::endl;
        return -1;
    }
    int epsilon{atoi(argv[1])};
    tangent_eq t;
    secant s (pow(10, -epsilon));

    for (int i{0}; i <= 20; i++)
    {
        std::cout << "\nInterval (" << i << "pi, " << i << "pi + pi/2):" << std::endl;
        double root{s.find_roots(i*M_PI, (i*M_PI + M_PI_2), t)};
        std::cout << std::fixed << std::setprecision(-log10(s.get_precision()))<< root << std::endl << std::endl;
    }

    return 0;
}
