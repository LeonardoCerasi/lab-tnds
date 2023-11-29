#pragma once

#include <cassert>

#include "random_gen.h"

namespace test
{
    bool are_close(double calculated, double expected, double epsilon = 1e-7)
    {
        return (std::fabs(calculated - expected) < epsilon);
    }

    void test_random(void)
    {
        random_gen rand_1{1};

        assert(are_close(rand_1.random(), 0.47291105054318905));
        assert(are_close(rand_1.random(), 0.7385413474403322));
        assert(are_close(rand_1.random(), 0.008484064601361752));
        assert(are_close(rand_1.random(), 0.40976652735844254));
        assert(are_close(rand_1.random(), 0.10108725726604462));

        random_gen rand_2{1};

        assert(are_close(rand_2.exp(1), 0.6403859601352556));
        assert(are_close(rand_2.exp(1), 1.3414791243855002));
        assert(are_close(rand_2.exp(1), 0.008520259140710315));
        assert(are_close(rand_2.exp(1), 0.5272371040158115));
        assert(are_close(rand_2.exp(1), 0.10656930958385337));

        random_gen rand_3{1};

        assert(are_close(rand_3.gauss_bm(2, 1), 1.9185906933235062));
        assert(are_close(rand_3.gauss_bm(2, 1), 1.8898847197814346));
        assert(are_close(rand_3.gauss_bm(2, 1), 1.9682233298032183));
        assert(are_close(rand_3.gauss_bm(2, 1), 2.960947466486181));
        assert(are_close(rand_3.gauss_bm(2, 1), 1.9538792463229713));

        random_gen rand_4{1};

        assert(are_close(rand_4.gauss_ar(2, 1), 1.7291105054318905));
        assert(are_close(rand_4.gauss_ar(2, 1), 2.4952592495828867));
        assert(are_close(rand_4.gauss_ar(2, 1), 2.009022830054164));
        assert(are_close(rand_4.gauss_ar(2, 1), 0.6520544346421957));
        assert(are_close(rand_4.gauss_ar(2, 1), 1.318840131163597));
    }
}
