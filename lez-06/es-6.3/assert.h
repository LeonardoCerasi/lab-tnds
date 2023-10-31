#include <cmath>
#include <cassert>

#include "functions.h"
#include "bisection.h"

namespace test
{
    bool are_close(double calculated, double expected, double epsilon = 1e-7)
    {
        return (fabs(calculated - expected) < epsilon);
    }

    void test_bisection(void)
    {
        parabola p (3, 5, -2);
        bisection b (1e-8);

        assert(are_close(b.find_roots(-3., -1., p), -2.));
        assert(are_close(b.find_roots(-2., 0., p), -2.));
        assert(are_close(b.find_roots(-4., -2., p), -2.));

        assert(are_close(b.find_roots(0., 1., p), 1. / 3.));
    }

}