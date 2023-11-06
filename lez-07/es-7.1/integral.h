#pragma once

#include <functional>

class numeric_integral
{
    public:

        numeric_integral() {}
        virtual ~numeric_integral() {}

        virtual double integral(double, double, std::function<double (double)>, int) = 0;  
};
