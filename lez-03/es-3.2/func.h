#pragma once

// includes

#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <vector>
#include <algorithm>

// declarations

namespace test
{
    bool approximation(double calculated, double expected, double sensibility);

    void test_stat(void);
}

template <typename Type>
std::vector<Type> read_file(const char *path, int n_data);

namespace stat
{
    template <typename Type>
    double mean(const std::vector<Type> &vect);

    template <typename Type>
    double variance(const std::vector<Type> &vect);

    template <typename Type>
    double median(std::vector<Type> &vect);
}

template <typename Type>
void print(const char *path, const std::vector<Type> &vect);

template <typename Type>
void print(const std::vector<Type> &vect);

// implementation

bool test::approximation(double calculated, double expected, double sensibility = 1e-7)
{
    return (fabs(calculated - expected) < sensibility);
}

void test::test_stat(void)
{
    std::vector<double> vect(4);
    for (int i = 0; i < vect.size(); i++)
    {
        vect[i] = i + 1;
    }

    assert(test::approximation(stat::mean(vect), 2.5));
    assert(test::approximation(stat::variance(vect), 1.25));
    assert(test::approximation(stat::median(vect), 2.5));
}

template <typename Type>
std::vector<Type> read_file(const char *path, int n_data)
{
    std::ifstream input(path);

    if (!input)
    {
        std::cerr << "Error while opening file." << std::endl;
    }

    std::vector<Type> vect(n_data);

    for (int i = 0; i < n_data; i++)
    {
        Type temp;
        input >> temp;

        if (input.eof())
        {
            std::cerr << "Reached end of file at line " << i << " before given data number " << n_data << " was reached." << std::endl;

            break;
        }

        vect[i] = temp;
    }

    input.close();

    return vect;
}

template <typename Type>
double stat::mean(const std::vector<Type> &vect)
{
    double mean = 0;

    for (int i = 0; i < vect.size(); i++)
    {
        mean += vect[i];
    }

    return (mean / double(vect.size()));
}

template <typename Type>
double stat::variance(const std::vector<Type> &vect)
{
    double mean = stat::mean(vect);
    double variance = 0;

    for (int i = 0; i < vect.size(); i++)
    {
        variance += pow(vect[i] - mean, 2);
    }

    return (variance / double(vect.size()));
}

template <typename Type>
double stat::median(std::vector<Type> &vect)
{
    std::sort(vect.begin(), vect.end());

    if (vect.size() % 2 == 0)
    {
        return (vect[vect.size() / 2 - 1] + vect[vect.size() / 2]) / 2;
    }
    else
    {
        return vect[vect.size() / 2 - 1];
    }
}

template <typename Type>
void print(const char *path, const std::vector<Type> &vect)
{
    std::ofstream output(path);

    output << "Reordered data:\n"
           << std::endl;
    for (int i = 0; i < vect.size(); i++)
    {
        output << vect[i] << std::endl;
    }

    output.close();
}

template <typename Type>
void print(const std::vector<Type> &vect)
{
    for (int i = 0; i < vect.size(); i++)
    {
        std::cout << vect[i] << std::endl;
    }
}
