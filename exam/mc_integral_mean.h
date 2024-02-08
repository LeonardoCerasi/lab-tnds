#pragma once

#include "mc_integral.h"

class mc_int_mean : public mc_integral
{
    public:

        mc_int_mean(unsigned int seed) : mc_integral{seed} {}

        double integral(const std::function<double (double)>, double, double, int) override;
};
