#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdexcept>

#include "midpoint.h"
#include "mc_integral_mean.h"

inline double mean(std::vector<double> &v)
{
    double sum;
    for (double x : v) { sum += x; }
    return (sum / (double)v.size());
}

inline double std_dev(std::vector<double> &v)
{
    double m{mean(v)};
    double sum{};
    for (double x : v) { sum += std::pow((x - m), 2); }
    return std::sqrt(sum / ((double)v.size() - 1.));
}

inline double exponent(std::vector<double> &h, std::vector<double> &err)
{
    std::vector<double> exp_v{};

    for (int i{}; i < (int)h.size() - 1; i++)
    {
        for (int j{i+1}; j < (int)h.size(); j++)
        {
            exp_v.push_back(std::log(err.at(i) / err.at(j)) / std::log(h.at(i) / h.at(j)));
        }
    }

    return mean(exp_v);
}

inline double coefficent(std::vector<double> &h, std::vector<double> &err, double exponent)
{
    std::vector<double> coeff_v{};

    for (int i{}; i < (int) h.size(); i++)
    {
        coeff_v.push_back(err.at(i) / std::pow(h.at(i), exponent));
    }

    return mean(coeff_v);
}

inline std::vector<double> analysis(std::function<double (double)> f, double a, double b, double value, double n, int type = 0)
{
    midpoint calc{};
    std::cout << "The integral evaluates to: " << calc.integral(a, b, f, 10000, type) << std::endl;

    std::vector<double> h_v{}, err_v{};

    for (int i{1}; i <= n; i++)
    {
        h_v.push_back((b - a) / std::pow(2, i));
        err_v.push_back(std::fabs(calc.integral(a, b, f, std::pow(2, i), type) - value));
    }

    std::cout << "\nError as a function of integration step:" << std::endl;
    std::cout << "n\t" << "h\t\t" << "σ" << std::endl;
    for (int i{}; i < (int)err_v.size(); i++)
    {
        std::cout << std::fixed << std::setprecision(0) << std::pow(2, i + 1) << "\t" << std::setprecision(8) << h_v.at(i) << "\t" << err_v.at(i) << std::endl;
    }

    double expon{exponent(h_v, err_v)};
    double coeff{coefficent(h_v, err_v, expon)};
    std::cout << "\nσ = " << coeff << " * h ^ " << expon << std::endl;

    std::vector<double> parameters{expon, coeff};

    return parameters;
}
