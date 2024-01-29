#include "bisection.h"

bisection::bisection (double epsilon) : roots(epsilon) {}

bisection::bisection (double epsilon, int max_iter) : roots(epsilon, max_iter) {}

double bisection::find_roots (double x_min, double x_max, std::function<double (double)> func)
{
    int n_iter = 0;

    if (x_min < x_max) {a = x_min; b = x_max;}
    else {a = x_max; b = x_min;}

    double fa = func(a);
    double fb = func(b);
    double c, fc;

    while (((b - a) > precision) && (n_iter < n_max))
    {
        c = (a + b) / 2;
        fc = func(c);

        if (sign(fa) * sign(fc) < 0) { b = c; fb = fc; }
        else if (sign(fc) * sign(fb) < 0) { a = c; fa = fc; }
        else { return (fa == 0 ? a : (fb == 0 ? b : c)); }

        n_iter++;
    }

    return ((a + b) / 2);
}
