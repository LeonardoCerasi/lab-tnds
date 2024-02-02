#pragma once

#include <cmath>
#include <string>
#include <fstream>
#include <filesystem>
#include <functional>

#include "random_gen.h"
#include "mc_multi_integral_mean.h"
#include "func.h"

void integrals_multi(multi_integral mc_multi, std::function<double (std::vector<double>)> func, std::vector<double> a, std::vector<double> b, int N, int NUMBER)
{
    std::string path{"data/log_multi_" + std::to_string(N) + ".dat"};
    std::filesystem::path file_path{path};

    if (!std::filesystem::exists(file_path))
    {
        std::ofstream file{path};

        for (int i{}; i < NUMBER; i++) { file << mc_multi.integral(func, a, b, N) << std::endl; }
    }
}
