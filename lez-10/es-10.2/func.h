#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <fstream>

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

double mean(std::vector<double> v)
{
    double sum;
    for (double x : v) { sum += x; }
    return (sum / (double)v.size());
}

double std_dev(std::vector<double> v)
{
    double m{mean(v)};
    double sum{};
    for (double x : v) { sum += std::pow((x - m), 2); }
    return std::sqrt(sum / ((double)v.size() - 1.));
}

std::vector<double> read_file(std::string path)
{
    std::ifstream input(path);

    std::vector<double> vect;

    while (!input.eof())
    {
        double temp;
        input >> temp;

        vect.push_back(temp);
    }

    input.close();

    return vect;
}
