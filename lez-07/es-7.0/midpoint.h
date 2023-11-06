#pragma once

#include "integral.h"

class midpoint : public numeric_integral
{
public:
    midpoint() {}
    ~midpoint() {}

    double integral(double, double, std::function<double(double)>, int) override;
};
