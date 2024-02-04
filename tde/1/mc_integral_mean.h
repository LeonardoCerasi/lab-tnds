#pragma once

#include "mc_integral.h"
#include "func.h"

class mc_int_mean : public mc_integral
{
    public:

        mc_int_mean(unsigned int seed) : mc_integral{seed} {}

        double integral(const std::function<double (double)>, double, double, int) override;
        std::vector<double> integrate(const std::function<double (double)>, double, double, int, int);
};
