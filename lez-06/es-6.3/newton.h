#pragma once

#include <iostream>

#include "func.h"
#include "roots.h"

class newton : public roots
{
public:
    newton() {}
    newton(double);
    newton(double, int);
    virtual ~newton() {}

    virtual double find_roots(double, double, const function &) override;
};
