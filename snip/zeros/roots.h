#pragma once

#include <iostream>
#include <functional>
#include <stdexcept>

class roots
{
    public:

        virtual double find_roots(double, double, std::function<double (double)>, int, double) = 0;
};
