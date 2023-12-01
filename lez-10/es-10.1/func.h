#pragma once

#include <cmath>
#include <vector>

std::vector<double> sum_elements(std::vector<double> v, int n)
{
    std::vector<double> sums;

    double acc{};
    for (int i{1}; i <= (int)v.size(); i++)
    {
        acc += v[i-1];

        if (i % n == 0)
        {
            sums.push_back(acc);
            acc = 0;
        }
    }

    return sums;
}

double mean(std::vector<double> v)
{
    double sum;
    for (double x : v) { sum += x; }
    return (sum / (double)v.size());
}

double variance(std::vector<double> v)
{
    double m{mean(v)};
    double sum{};
    for (double x : v) { sum += std::pow((x - m), 2); }
    return (sum / ((double)v.size() - 1.));
}
