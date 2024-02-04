#include <iostream>
#include <cmath>
#include <vector>

#include "midpoint.h"
#include "func.h"
#include "mc_integral_mean.h"

#define E 2.718281828
#define NUMBER 1000

int main()
{
    auto f{[] (double x) -> double { return std::pow(x, 3) * std::log(std::sqrt(E + std::pow(x, 2))); }};
    double a{0.}, b{std::sqrt(E)};
    double value{3. * std::pow(E, 2) / 16.};

    std::vector<double> error_midpoint{analysis(f, a, b, value, 10)};

    ////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "\n\n-----------------\n\n" << std::endl;
    std::cout << "Now using \"midright\" method.\n" << std::endl;

    std::vector<double> error_midright{analysis(f, a, b, value, 10, 1)};

    ////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "\n\n-----------------\n\n" << std::endl;
    std::cout << "Now using mean method.\n" << std::endl;

    try
    {
        int N{16};
        mc_int_mean calc_mean{1};

        std::vector<double> mean_int{calc_mean.integrate(f, a, b, N, NUMBER)};

        std::cout << "The integral evaluates to: " << mean_int.at(0) << " ± " << mean_int.at(1) << std::endl;

        midpoint calc{};
        double prec{std::fabs(calc.integral(a, b, f, 16) - value)};
        
        // assuming σ_I = σ_f * (b - a) / sqrt(N)
        double N_req{N * std::pow(mean_int.at(1) / prec, 2)};

        std::cout << "\nIn order to have the same error as with midpoint method N must be: " << (int)std::round(N_req) << std::endl;
    }
    catch(const std::exception &e) { std::cerr << e.what() << std::endl; }

    ////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "\n\n-----------------\n\n" << std::endl;
    std::cout << "New integral with midpoint (\"midright\" diverges as f(2) = inf).\n" << std::endl;

    auto f_2{[] (double x) -> double { return 1. / std::sqrt(4 - x*x); }};
    double a_2{0.}, b_2{2};
    double value_2{M_PI_2};

    analysis(f_2, a_2, b_2, value_2, 10);

    return 0;
}
