#include <iostream>
#include <iomanip>
#include <cmath>

#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"

#include "trapezoidal.h"

int main (int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <epsilon>" << std::endl;
        return -1;
    }

    int epsilon{atoi(argv[1])};
    double precision{std::pow(10, -epsilon)};

    auto func {[] (double x) -> double { return std::sin(x); }};
    trapezoidal integ;

    std::cout << "\n" << epsilon << ": " << std::fixed << std::setprecision(epsilon) << integ.integral(0, M_PI, func, precision) << std::endl << std::endl;

    return 0;
}
