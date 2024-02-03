#pragma once

#include "random_gen.h"

#define g 9.81 // m/s²

class viscosity
{
    private:

    random_gen rand_gen;

        double ρ, ρ0;
        double η_i, r_i, x1_i, x2_i, Δt_i;
        double η_m, r_m, x1_m, x2_m, Δt_m;
        double σ_t, σ_x, σ_r; 

    public:

        viscosity(unsigned int, double, double, double, double, double, double, double, double, double);

        void measure();
        void analysis();

        double get_η_m() { return η_m; }
};
