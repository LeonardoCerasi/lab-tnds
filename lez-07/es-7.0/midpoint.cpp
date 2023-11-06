#include "midpoint.h"

double midpoint::integral(double x_min, double x_max, std::function<double(double)> func, int n_steps)
{
    double a, b;
    if (x_min < x_max) { a = x_min; b = x_max; }
    else { a = x_max; b = x_min; }

    double h {(b - a) / n_steps};
    double integ {};
    for (int i {}; i < n_steps; i++) { integ += func(a + (i + 0.5) * h); }

    return (integ * h);
}
