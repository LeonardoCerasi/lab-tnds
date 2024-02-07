#pragma once

#include <cmath>

#include "random_gen.h"

class capacitor
{
    private:

        random_gen rand_gen{1};

        double V_0_i, V_1_i, R_i, C_i, t_i;
        double V_0_m, V_1_m, R_m, C_m, t_m;
        double perc_V_0, perc_V_1, perc_R, perc_t;
    
    public:

        capacitor(double V_0, double V_1, double C, double R, double p_V_0, double p_V_1, double p_R, double p_t) : V_0_i{V_0}, V_1_i{V_1}, R_i{R}, C_i{C}, perc_V_0{p_V_0}, perc_V_1{p_V_1}, perc_R{p_R}, perc_t{p_t}
        {
            t_i = C_i * R_i * std::log(V_0_i / V_1_i);
        }

        void measure()
        {
            V_0_m = rand_gen.gauss_bm(V_0_i, perc_V_0 * V_0_i);
            V_1_m = rand_gen.gauss_bm(V_1_i, perc_V_1 * V_1_i);
            R_m = rand_gen.gauss_bm(R_i, perc_R * R_i);
            t_m = rand_gen.gauss_bm(t_i, perc_t * t_i);
        }

        void analysis()
        {
            C_m = t_m / (R_m * std::log(V_0_m / V_1_m));
        }

        double get_C() { return C_m; }
};
