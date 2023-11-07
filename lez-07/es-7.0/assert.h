#pragma once

#include <cmath>
#include <cassert>

#include "midpoint.h"

namespace test
{
    bool are_close(double calculated, double expected, double epsilon = 1e-7)
    {
        return (fabs(calculated - expected) < epsilon);
    }

    void test_midpoint(void)
    {
        auto func {[] (double x) -> double { return std::sin(x); }};
        midpoint integ;

        assert(are_close(integ.integral(0, M_PI, func, 10), 2.0082484079079745));
        assert(are_close(integ.integral(0, M_PI, func, 100), 2.000082249070986));
        assert(are_close(integ.integral(M_PI, 0, func, 10), -2.0082484079079745));
        assert(are_close(integ.integral(0, 1, func, 10), 0.45988929071851814));
        assert(are_close(integ.integral(1, 2, func, 30), 0.9564934239032155));
    }
}
