#pragma once

#include <iostream>
#include <functional>

#include "sign.h"
#include "roots.h"

class bisection : public roots
{
    public:

        bisection () {}
        bisection (double);
        bisection (double, int);
        virtual ~bisection () {}

        virtual double find_roots(double, double, std::function<double(double)> func) override;
};
