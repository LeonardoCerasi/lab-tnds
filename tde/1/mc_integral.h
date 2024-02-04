#pragma once

#include <functional>
#include <stdexcept>

#include "random_gen.h"

class mc_integral
{
    protected:

        random_gen rand_gen;
    
    public:

        mc_integral(unsigned int seed) : rand_gen{seed} {}
        virtual ~mc_integral() {}

        virtual double integral(const std::function<double (double)>, double, double, int) = 0;
};
