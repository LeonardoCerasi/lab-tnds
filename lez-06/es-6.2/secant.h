#pragma once

#include <iostream>

#include "sign.h"
#include "func.h"
#include "roots.h"

class secant : public roots
{
public:
    secant () {}
    secant (double);
    secant (double, int);
    virtual ~secant () {}

    virtual double find_roots (double, double, const function &) override;
};
