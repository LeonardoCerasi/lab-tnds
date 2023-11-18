#pragma once

#include <cassert>
#include <array>
#include <cmath>

#include "arr_op.h"

namespace test
{
    bool are_close(double calculated, double expected, double epsilon = 1e-7)
    {
        return (std::fabs(calculated - expected) < epsilon);
    }

    void test_array(void)
    {
        std::array<double, 3> arr_1{2.0, 4.0, 6.0};
        std::array<double, 3> arr_2{-1.0, 1.0, 4.0};

        std::array<double, 3> sum{arr_1 + arr_2};
        assert((sum[0] == 1.0) && (sum[1] == 5.0) && (sum[2] == 10.0));

        auto sub{arr_1 - arr_2};
        assert((sub[0] == 3.0) && (sub[1] == 3.0) && (sub[2] == 2.0));

        auto prod_sx{5.0 * arr_1};
        assert((prod_sx[0] == 10.0) && (prod_sx[1] == 20.0) && (prod_sx[2] == 30.0));

        auto prod_dx{arr_2 * 6.0};
        assert((prod_dx[0] == -6.0) && (prod_dx[1] == 6.0) && (prod_dx[2] == 24.0));

        auto ratio{arr_1 / 2.0};
        assert((ratio[0] == 1.0) && (ratio[1] == 2.0) && (ratio[2] == 3.0));
    }
}
