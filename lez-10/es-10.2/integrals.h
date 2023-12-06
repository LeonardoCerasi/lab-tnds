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

int n_precision(std::vector<int> numbers, std::vector<double> errors, double prec)
{
    prec = std::log10(prec);
    for (int i{}; i < (int)numbers.size(); i++)
    {
        numbers[i] = std::log10(numbers[i]);
        errors[i] = std::log10(errors[i]);
    }

    std::vector<double> n;
    for (int i{}; i < (int)numbers.size() - 1; i++)
    {
        for (int j{i + 1}; j < (int)numbers.size(); j++)
        {
            n.push_back(numbers[i] + (prec - errors[i]) * (numbers[i] - numbers[j]) / (errors[i] - errors[j]));
        }
    }

    double n_prec{mean(n)};
    return (int)std::pow(10, n_prec);
}
