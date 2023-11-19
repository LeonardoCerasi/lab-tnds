#pragma once

#include <vector>

#include "arr_op.h"
#include "runge_kutta.h"
#include "sign.h"

int find_inversion(std::vector<double> time, std::vector<double> velocity, double t)
{
    int index{};
    for (int i{}; i < (int)time.size(); i++)
    {
        if (time[i] > t)
        {
            index = i;
            break;
        }
    }

    for (int i{index}; i < (int) velocity.size(); i++)
    {
        if (sign(velocity[i]) * sign(velocity[i+1]) < 0.) { return i; }
    }

    return __INT_MAX__;
}

double find_amplitude(std::vector<double> time, std::vector<double> position, std::vector<double> velocity, double t)
{
    int i_inv_1{find_inversion(time, velocity, t)};
    double t_inv_1{time[i_inv_1] + (0. - time[i_inv_1 + 1]) * (time[i_inv_1] - time[i_inv_1 + 1]) / (velocity[i_inv_1] - velocity[i_inv_1 + 1])};
    int i_inv_2{find_inversion(time, velocity, t_inv_1)};
    double t_inv_2{time[i_inv_2] + (0. - time[i_inv_2 + 1]) * (time[i_inv_2] - time[i_inv_2 + 1]) / (velocity[i_inv_2] - velocity[i_inv_2 + 1])};

    while (sign(position[i_inv_1]) * sign(position[i_inv_2]) > 0.)
    {
        i_inv_2 = find_inversion(time, velocity, t_inv_2);
        t_inv_2 = time[i_inv_2] + (0. - time[i_inv_2 + 1]) * (time[i_inv_2] - time[i_inv_2 + 1]) / (velocity[i_inv_2] - velocity[i_inv_2 + 1]);
    }

    double amplitude{std::fabs(position[i_inv_1] - position[i_inv_2]) / 2.};

    std::cout << "\n\n"
              << i_inv_1 << "\t\t" << i_inv_2 << "\n"
              << t_inv_1 << "\t\t" << t_inv_2 << "\n"
              << position[i_inv_1] << "\t" << position[i_inv_2]
              << std::endl;
    
    return amplitude;
}
