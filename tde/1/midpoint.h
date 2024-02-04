#pragma once

#include "integral.h"

class midpoint : public numeric_integral
{
    private:

        double calculate(double, double, std::function<double (double)>, int, int type = 0);
        
    public:

        double integral(double, double, std::function<double(double)>, int, int type = 0) override;
};
