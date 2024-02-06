#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>

double max(const std::vector<double> &v)
{
    double x{v[0]};
    for (int i{1}; i < (int)v.size(); i++) { if (v[i] > x) { x = v[i]; } }
    return x;
}

double min(const std::vector<double> &v)
{
    double x{v[0]};
    for (int i{1}; i < (int)v.size(); i++) { if (v[i] < x) { x = v[i]; } }
    return x;
}

double mean(std::vector<double> &v)
{
    double sum{};
    for (double x : v) { sum += x; }
    return (sum / (double)v.size());
}

double std_dev(std::vector<double> &v)
{
    double m{mean(v)};
    double sum{};
    for (double x : v) { sum += std::pow((x - m), 2); }
    return std::sqrt(sum / ((double)v.size() - 1.));
}

double corr(std::vector<double> &v_1, std::vector<double> &v_2)
{
    if (v_1.size() != v_2.size()) { throw std::invalid_argument("corr : datasets must have the same dimension."); }

    double mean_1{}, mean_2{};
    for (int i{}; i < (int)v_1.size(); i++) { mean_1 += v_1[i]; mean_2 += v_2[i]; }
    mean_1 = mean_1 / (double)v_1.size();
    mean_2 = mean_2 / (double)v_2.size();

    double sum{};
    for (int i{}; i < (int)v_1.size(); i++) { sum += (v_1[i] - mean_1) * (v_2[i] - mean_2); }
    double sum_1{};
    for (int i{}; i < (int)v_1.size(); i++) { sum_1 += (v_1[i] - mean_1) * (v_1[i] - mean_1); }
    double sum_2{};
    for (int i{}; i < (int)v_1.size(); i++) { sum_2 += (v_2[i] - mean_2) * (v_2[i] - mean_2); }

    return sum / std::sqrt(sum_1 * sum_2);
}
