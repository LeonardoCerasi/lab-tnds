#pragma once

#include <functional>

#include "arr_op.h"

template <size_t N>
class differential_equation
{
    public:
        
        virtual std::array<double, N> step(double t, double h, const std::array<double, N> &x, std::function<std::array<double, N> (double)> f) const = 0;
};
