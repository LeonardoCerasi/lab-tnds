#include <iostream>
#include <cmath>
#include <string>

#include "random_gen.h"
#include "mc_integral_mean.h"
#include "assert.h"
#include "func.h"

#define NUMBER 100000

int main()
{
    test::test_random();

    multi_integral integ{1};

    auto func{[] (std::vector<double> x) -> double { return (10 + 5 * std::cos(4 * x[1]) * std::sin(7 * x[0]) / std::pow(x[0], 2)); }};
    std::vector<double> a{1, 2};
    std::vector<double> b{1, 2};

    std::cout << integ.integral(func, a, b, NUMBER) << std::endl;

    return 0;
}
