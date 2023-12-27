#pragma once

#include <iostream>
#include <cmath>
#include <vector>

double mean(std::vector<double> v)
{
    double sum;
    for (double x : v) { sum += x; }
    return (sum / (double)v.size());
}

double mean(std::vector<double> v, double n)
{
    double sum;
    for (double x : v) { sum += std::pow(x, n); }
    return (sum / (double)v.size());
}

double mean(std::vector<double> v_1, std::vector<double> v_2)
{
    double sum;
    for (int i{}; i < (int)v_1.size(); i++) { sum += v_1[i] * v_2[i]; }
    return (sum / (double)v_1.size());
}

double std_dev(std::vector<double> v)
{
    double m{mean(v)};
    double sum{};
    for (double x : v) { sum += std::pow((x - m), 2); }
    return std::sqrt(sum / ((double)v.size() - 1.));
}

double corr(std::vector<double> v_1, std::vector<double> v_2)
{
    std::cout << mean(v_1, v_2) - mean(v_1) * mean(v_2) << std::endl;
    std::cout << mean(v_1, 2) - std::pow(mean(v_1), 2) << std::endl;
    std::cout << mean(v_2, 2) - std::pow(mean(v_2), 2) << std::endl;

    return (mean(v_1, v_2) - mean(v_1) * mean(v_2)) / (std::sqrt(mean(v_1, 2) - std::pow(mean(v_1), 2)) * std::sqrt(mean(v_2, 2) - std::pow(mean(v_2), 2)));
}
