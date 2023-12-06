#pragma once

#include "mc_integral.h"

class mc_int_hm : public mc_integral
{
    public:

        mc_int_hm(unsigned int seed) : mc_integral{seed} {}

        double integral(const std::function<double (double)>, double, double, double, int, double) override;
};
