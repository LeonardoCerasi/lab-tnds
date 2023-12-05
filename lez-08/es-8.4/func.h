#pragma once

#include <vector>
#include <cmath>
#include <iostream>

#include "arr_op.h"
#include "runge_kutta.h"
#include "sign.h"

int find_inversion(std::vector<double> time, std::vector<double> velocity, double t, double h)
{
    for (int i{}; i < (int)time.size(); i++)
    {
        if ((time[i] >= t + h) && (sign(velocity[i]) * sign(velocity[i + 1]) < 0.)) { return i; }
    }

    return __INT_MAX__;
}

double find_amplitude(std::vector<double> time, std::vector<double> position, std::vector<double> velocity, double t, double h)
{
    std::cout << t << std::endl;

    int i_inv_1{find_inversion(time, velocity, t, h)};
    double t_inv_1{time[i_inv_1] + (0. - velocity[i_inv_1 + 1]) * (time[i_inv_1] - time[i_inv_1 + 1]) / (velocity[i_inv_1] - velocity[i_inv_1 + 1])};
    int i_inv_2{find_inversion(time, velocity, t_inv_1, h)};
    double t_inv_2{time[i_inv_2] + (0. - velocity[i_inv_2 + 1]) * (time[i_inv_2] - time[i_inv_2 + 1]) / (velocity[i_inv_2] - velocity[i_inv_2 + 1])};

    std::cout << i_inv_1 << "\t" << t_inv_1 << "\t" << position[i_inv_1] << std::endl;
    std::cout << i_inv_2 << "\t" << t_inv_2 << "\t" << position[i_inv_2] << std::endl;

    while (sign(position[i_inv_1]) * sign(position[i_inv_2]) > 0.)
    {
        i_inv_2 = find_inversion(time, velocity, t_inv_2, h);
        t_inv_2 = time[i_inv_2] + (0. - velocity[i_inv_2 + 1]) * (time[i_inv_2] - time[i_inv_2 + 1]) / (velocity[i_inv_2] - velocity[i_inv_2 + 1]);

        std::cout << i_inv_2 << "\t" << t_inv_2 << "\t" << position[i_inv_2] << std::endl;
    }

    double amplitude{std::fabs(position[i_inv_1] - position[i_inv_2]) / 2.};
    
    return amplitude;
}
