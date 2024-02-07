#pragma once

#include <cmath>
#include <stdexcept>

class random_gen
{
    private:

        unsigned int a, c, m, s;
        unsigned int r;

    public:

        random_gen(unsigned int);
        
        double random();
        double unif(double, double);
        double exp(double);
        double gauss_bm(double, double);
        double gauss_ar(double, double);

        void set_a(unsigned int);
        void set_c(unsigned int);
        void set_m(unsigned int);
};
