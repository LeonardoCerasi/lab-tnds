#include "secant.h"

double secant::find_roots(double x_min, double x_max, std::function<double(double)> func, int n_max, double precision)
{
    if (n_max < 0) { throw std::invalid_argument("secant::find_roots : number of steps must be positive."); }
    if (precision < 0) { throw std::invalid_argument("secant::find_roots : precision must be positive."); }

    int n_iter{};

    double a, b;
    if (x_min < x_max) { a = x_min; b = x_max; }
    else { a = x_max; b = x_min; }

    double fa{func(a)};
    double fb{func(b)};
    double c, fc;

    while (((b - a) > precision) && (n_iter < n_max))
    {
        c = b - (func(b) * (b - a)) / (func(b) - func(a));
        fc = func(c);

        if (sign(fa) * sign(fc) < 0) { b = c; fb = fc; }
        else if (sign(fc) * sign(fb) < 0) { a = c; fa = fc; }
        else { return (fa == 0 ? a : (fb == 0 ? b : c)); }

        n_iter++;
    }

    return (b - (func(b) * (b - a)) / (func(b) - func(a)));
}
