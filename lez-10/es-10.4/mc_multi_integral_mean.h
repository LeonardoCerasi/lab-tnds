#pragma once

#include <functional>
#include <stdexcept>

#include "random_gen.h"

class multi_integral
{
    protected:

        random_gen rand_gen;

    public:

        multi_integral(unsigned int seed) : rand_gen{seed} {}
        virtual ~multi_integral() {}

        double integral(const std::function<double(std::vector<double>)> func, std::vector<double> a, std::vector<double> b, int N)
        {
            if (a.size() != b.size()) { throw std::invalid_argument("The points given must have the same dimension."); }

            int sign{1};
            for (int i{}; i < (int)a.size(); i++)
            {
                if (b.at(i) < a.at(i)) { double c = a.at(i); a.at(i) = b.at(i); b.at(i) = c; sign *= -1; }
            }

            std::vector<std::vector<double>> rand_point;
            for (int i{}; i < N; i++)
            {
                std::vector<double> point;
                for (int j{}; j < (int)a.size(); j++) { point.push_back(rand_gen.unif(a.at(j), b.at(j))); }
                rand_point.push_back(point);
            }

            double hyper_volume{1.};
            for (int i{}; i < (int)a.size(); i++) { hyper_volume *= (b.at(i) - a.at(i)); }

            double integ{};
            for (std::vector<double> x : rand_point) { integ += func(x); }
            return (sign * integ * hyper_volume / (double)N);
        }
};
