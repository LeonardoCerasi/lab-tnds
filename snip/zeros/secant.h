#pragma once

#include <iostream>
#include <functional>

#include "sign.h"
#include "roots.h"

class secant : public roots
{
    public:
    
        virtual double find_roots(double, double, std::function<double (double)>, int, double) override;
};
