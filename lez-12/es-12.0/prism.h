#pragma once

#include <iostream>
#include <cmath>

#include "random_gen.h"

class prism
{
    private:

        random_gen rand_gen;

        double lambda_1, lambda_2, alpha, sigma_theta;

        double A_i, A_m;
        double B_i, B_m;

        double n_1_i, n_1_m;
        double n_2_i, n_2_m;

        double delta_1_i, delta_1_m;
        double delta_2_i, delta_2_m;

        double theta_0_i, theta_0_m;
        double theta_1_i, theta_1_m;
        double theta_2_i, theta_2_m;
    
    public:

        prism(unsigned int, double, double, double, double, double, double, double);

        void measures();
        void analysis();

        double get_A_i() const { return A_i; }
        double get_A_m() const { return A_m; }
        double get_B_i() const { return B_i; }
        double get_B_m() const { return B_m; }

        double get_n_1_i() const { return n_1_i; }
        double get_n_1_m() const { return n_1_m; }
        double get_n_2_i() const { return n_2_i; }
        double get_n_2_m() const { return n_2_m; }

        double get_delta_1_i() const { return delta_1_i; }
        double get_delta_1_m() const { return delta_1_m; }
        double get_delta_2_i() const { return delta_2_i; }
        double get_delta_2_m() const { return delta_2_m; }

        double get_theta_0_i() const { return theta_0_i; }
        double get_theta_0_m() const { return theta_0_m; }
        double get_theta_1_i() const { return theta_1_i; }
        double get_theta_1_m() const { return theta_1_m; }
        double get_theta_2_i() const { return theta_2_i; }
        double get_theta_2_m() const { return theta_2_m; }

};
