#include "simpson.h"

double simpson::calculate(double a, double b, std::function<double(double)> func, int n_steps)
{
    double h {(b - a) / n_steps};
    double integ {func(a) + func(b)};
    for (int i {1}; i < n_steps; i++) { integ += 2 * (1 + i % 2) * func(a + i * h); }

    return (integ * h / 3.);
}


double simpson::integral(double x_min, double x_max, std::function<double(double)> func, int n_steps)
{
    if (n_steps < 0) { throw std::invalid_argument("simpson::integral : number of steps must be positive."); }

    double a, b;
    int sign{1};
    if (x_min < x_max) { a = x_min; b = x_max; }
    else { a = x_max; b = x_min; sign = -1; }

    return (sign * calculate(a, b, func, n_steps));
}
