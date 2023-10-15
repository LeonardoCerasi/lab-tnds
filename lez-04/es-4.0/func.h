#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>

template <typename Type>
std::vector<std::vector<Type>> read_file(const char *path)
{
    std::vector<std::vector<Type>> array;

    std::ifstream input (path);

    if (!input)
    {
        std::string path_s (path); 
        throw std::invalid_argument("Error while opening " + path_s + " : file does not exist.");
    }

    // std::vector<Type> temp_v;
    // std::string temp_s;
    // Type temp_t;
    // 
    // getline(input, temp_s);
    // while (!input.eof())
    // {
    //     std::stringstream temp_ss (temp_s);
    //     while (temp_ss >> temp_t)
    //     {
    //         temp_v.push_back(temp_t);
    //     }
    // 
    //     array.push_back(temp_v);
    //     delete[] &temp_v;
    // 
    //     getline(input, temp_s);
    // }

    std::string temp;
    Type col_1, col_2, col_3;

    while (std::getline(input, temp))
    {
        std::stringstream temp_ss (temp);
        temp_ss >> col_1 >> col_2 >> col_3;

        array.push_back({col_1, col_2, col_3});
    }

    input.close();

    return array;
}

std::vector<double> linear_regression(std::vector<double> x, std::vector<double> y, std::vector<double> err)
{
    double df = y.size() - 2;

    double sum_p = 0;
    double sum_x = 0;
    double sum_y = 0;
    double sum_xx = 0;
    double sum_xy = 0;
    double sum_yy = 0;
    for (int i = 0; i < (int) y.size(); i++)
    {
        sum_p += (1/pow(err[i], 2));
        sum_x += (1 / pow(err[i], 2)) * x[i];
        sum_y += (1 / pow(err[i], 2)) * y[i];
        sum_xx += (1 / pow(err[i], 2)) * x[i] * x[i];
        sum_xy += (1 / pow(err[i], 2)) * x[i] * y[i];
        sum_yy += (1 / pow(err[i], 2)) * y[i] * y[i];
    }

    double delta_x = sum_p * sum_xx - sum_x * sum_x;
    double delta_y = sum_p * sum_yy - sum_y * sum_y;

    double inter = (sum_xx * sum_y - sum_x * sum_xy) / delta_x;
    double slope = (sum_p * sum_xy - sum_x * sum_y) / delta_x;
    
    double inter_err = sqrt(sum_xx / delta_x);
    double slope_err = sqrt(sum_p / delta_x);

    double r = slope * sqrt(delta_x / delta_y);

    return {slope, inter, slope_err, inter_err, df, r};
}
