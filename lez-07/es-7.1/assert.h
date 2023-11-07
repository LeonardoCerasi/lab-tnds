#pragma once

#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "simpson.h"

namespace test
{
    bool are_close(double calculated, double expected, double epsilon = 1e-7)
    {
        return (fabs(calculated - expected) < epsilon);
    }

    void test_simpson(void)
    {
        auto func{[](double x) -> double
                  { return std::sin(x); }};
        simpson integ;

        assert(are_close(integ.integral(0, M_PI, func, 10), 2.0001095173150043));
        assert(are_close(integ.integral(0, M_PI, func, 100), 2.000000010824504));
        assert(are_close(integ.integral(M_PI, 0, func, 10), -2.0001095173150043));
        assert(are_close(integ.integral(0, 1, func, 10), 0.45969794982382056));
        assert(are_close(integ.integral(1, 2, func, 30), 0.9564491489761575));
    }
}
