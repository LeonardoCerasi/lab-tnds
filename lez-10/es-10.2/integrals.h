#pragma once

#include <cmath>
#include <string>
#include <fstream>
#include <filesystem>
#include <functional>

#include "random_gen.h"
#include "mc_integral_mean.h"
#include "mc_integral_hm.h"
#include "assert.h"
#include "func.h"

void integrals_mean(mc_int_mean mc_mean, std::function<double (double)> func, double a, double b, double f_max, int N, double prec, int NUMBER)
{
    std::string path{"data/log_mean_" + std::to_string(N) + ".dat"};
    std::filesystem::path file_path{path};

    if (!std::filesystem::exists(file_path))
    {
        std::ofstream file{path};

        for (int i{}; i < NUMBER; i++) { file << mc_mean.integral(func, 0, M_PI, 1, N, prec) << std::endl; }
    }
}

void integrals_hm(mc_int_hm mc_hm, std::function<double(double)> func, double a, double b, double f_max, int N, double prec, int NUMBER)
{
    std::string path{"data/log_hm_" + std::to_string(N) + ".dat"};
    std::filesystem::path file_path{path};

    if (!std::filesystem::exists(file_path))
    {
        std::ofstream file{path};

        for (int i{}; i < NUMBER; i++)
        {
            file << mc_hm.integral(func, 0, M_PI, 1, N, prec) << std::endl;
        }
    }
}
