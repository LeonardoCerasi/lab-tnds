#pragma once

#include <functional>
#include <stdexcept>

class numeric_integral
{
    public:

        virtual ~numeric_integral() {}

        virtual double integral(double, double, std::function<double (double)>, int) = 0;
        virtual double integral_prec(double, double, std::function<double (double)>, double) = 0;
};
