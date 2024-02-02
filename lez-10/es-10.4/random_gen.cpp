#include "random_gen.h"
#include <iostream>

random_gen::random_gen(unsigned int S) : a{1664525}, c{1013904223}, m{(unsigned int)std::pow(2, 31)}, s{S}, r{S} {}

double random_gen::random()
{
    r = (a * r + c) % m;
    return ((double)r / (double)m);
}

double random_gen::unif(double x_min, double x_max)
{
    return (x_min + (x_max - x_min) * random());
}

double random_gen::exp(double lambda)
{
    return (-std::log(1 - random()) / lambda);
}

double random_gen::gauss_bm(double mean, double sigma)
{
    return (mean + sigma * std::sqrt(-2 * std::log(1 - random())) * std::cos(2 * M_PI * random()));
}

double random_gen::gauss_ar(double mean, double sigma)
{
    double x{unif(-5., 5.)};
    double y{random()};

    while (y > (std::exp(-x * x / 2)))
    {
        x = unif(-5., 5.);
        y = random();
    }

    return (mean + sigma * x);
}

void random_gen::set_a(unsigned int A) { a = A; }
void random_gen::set_c(unsigned int C) { c = C; }
void random_gen::set_m(unsigned int M) { m = M; }
