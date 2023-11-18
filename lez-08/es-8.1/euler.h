#pragma once

#include "diff_eq.h"

template <size_t N>
class euler : public differential_equation<N>
{
    public:

        std::array<double, N> step(double t, double h, const std::array<double, N> &x, std::function<std::array<double, N> (double, const std::array<double, N> &)> f) const override
        {
            return (x + h * f(t, x));
        }
};
