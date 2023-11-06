#pragma once

#include "integral.h"

class trapezoidal : public numeric_integral
{
    public:

        double integral(double, double, std::function<double(double)>, int) override;
};
