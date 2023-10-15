#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>

std::vector<std::vector<double>> read_file(const char *path)
{
    std::vector<std::vector<double>> array;

    std::ifstream input(path);

    if (!input)
    {
        std::string path_s(path);
        throw std::invalid_argument("Error while opening " + path_s + " : file does not exist.");
    }

    std::vector<double> row;
    std::string line;
    std::string cell;
    while (std::getline(input, line))
    {
        std::stringstream temp_ss (line);
        
        while (std::getline(temp_ss, cell, ','))
        {
            row.push_back(atof(cell.c_str()));
        }

        array.push_back(row);
        row.erase(row.begin(), row.end());
    }

    input.close();

    return array;
}
