#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>

template <typename Type>
std::vector<Type> read_file(const char *path)
{
    std::vector<Type> array;

    std::ifstream input(path);

    if (!input)
    {
        std::string path_s(path);
        throw std::invalid_argument("Error while opening " + path_s + " : file does not exist.");
    }

    Type temp;
    while (input >> temp)
    {
        array.push_back(temp);
    }

    input.close();

    return array;
}

double S_function(double q, std::vector<double> data)
{
    double sum = 0;

    for (int i = 0; i < (int) data.size(); i++)
    {
        sum += pow((q - (data[i] / round(data[i] / q))), 2);
    }

    return sum;
}
