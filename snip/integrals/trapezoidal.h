#pragma once

#include <cmath>

#include "integral.h"

class trapezoidal : public numeric_integral
{
    private:

        double sigma(double, double, std::function<double (double)>, int);
        double int_sigma(double, double, std::function<double (double)>, int);

    public:

        double integral_prec(double, double, std::function<double(double)>, double) override;
};
