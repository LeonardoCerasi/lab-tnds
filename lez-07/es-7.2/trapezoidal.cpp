#include "trapezoidal.h"

double trapezoidal::sigma(double a, double b, std::function<double (double)> func, int n)
{
    double sum{(func(a) + func(b)) / 2.};

    for (int i{1}; i < std::pow(2, n); i++)
    {
        sum += func(a + i * (b - a) / std::pow(2, n));
    }

    return sum;
}

double trapezoidal::int_sigma(double a, double b, std::function<double(double)> func, int n)
{
    return ( sigma(a, b, func, n) * (b - a) / std::pow(2, n));
}

double trapezoidal::integral(double x_min, double x_max, std::function<double(double)> func, double precision)
{
    double a, b;
    if (x_min < x_max) { a = x_min; b = x_max; }
    else { a = x_max; b = x_min; }

    int n{};
    double int_1{int_sigma(a, b, func, n)}, int_2{int_sigma(a, b, func, n + 1)};

    while ((4 * std::fabs(int_2 - int_1) / 3.) > precision)
    {
        n++;
        int_1 = int_2;
        int_2 = int_sigma(a, b, func, n + 1);
    }

    return int_2;
}
