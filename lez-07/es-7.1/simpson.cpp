#include "simpson.h"

double trapezoidal::integral(double x_min, double x_max, std::function<double(double)> func, int n_steps)
{
    double a, b;
    if (x_min < x_max) { a = x_min; b = x_max; }
    else { a = x_max; b = x_min; }

    double h {(b - a) / n_steps};
    double integ {func(a) + func(b)};

    for (int i {}; i < n_steps; i++)
    {
        if (i % 2 == 0) { integ += 2 * func(a + i * h); }
        else { integ += 4 * func(a + i * h); }
    }

    return (integ * h / 3.);
}
