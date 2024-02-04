#include "midpoint.h"

double midpoint::calculate(double a, double b, std::function<double(double)> func, int n_steps, int type)
{
    // checks for midright
    double add{0.5};
    if (type == 1) { add = 1; }

    double h{(b - a) / n_steps};
    double integ{};
    for (int i{}; i < n_steps; i++) { integ += func(a + (i + add) * h); }

    return (integ * h);
}

double midpoint::integral(double x_min, double x_max, std::function<double(double)> func, int n_steps, int type)
{
    if (n_steps < 0) { throw std::invalid_argument("midpoint::integral : number of steps must be positive."); }

    double a, b;
    int sign{1};
    if (x_min < x_max) { a = x_min; b = x_max; }
    else { a = x_max; b = x_min; sign = -1; }

    return (sign * calculate(a, b, func, n_steps, type));
}
