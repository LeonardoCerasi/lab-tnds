#pragma once

#include <iostream>

#include "func.h"
#include "roots.h"

class bisection : public roots
{
    public:

        bisection () {}
        bisection (double);
        bisection (double, int);
        virtual ~bisection() {}

        virtual double find_roots (double, double, const function &) override;
};
