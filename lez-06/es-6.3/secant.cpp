#include "secant.h"

secant::secant (double epsilon) : roots(epsilon) {}

secant::secant (double epsilon, int max_iter) : roots(epsilon, max_iter) {}

double secant::find_roots(double x_min, double x_max, const function &func)
{
    int n_iter = 0;

    if (x_min < x_max)
    {
        a = x_min;
        b = x_max;
    }
    else
    {
        a = x_max;
        b = x_min;
    }

    double fa = func.eval(a);
    double fb = func.eval(b);
    double c, fc;

    while (((b - a) > precision) && (n_iter < n_max))
    {
        c = b - (func.eval(b) * (b - a)) / (func.eval(b) - func.eval(a));
        fc = func.eval(c);

        if ((fa == 0 ? 0 : (fa > 0 ? 1 : -1)) * (fc == 0 ? 0 : (fc > 0 ? 1 : -1)) < 0)
        {
            b = c;
            fb = fc;
        }
        else if ((fb == 0 ? 0 : (fb > 0 ? 1 : -1)) * (fc == 0 ? 0 : (fc > 0 ? 1 : -1)) < 0)
        {
            a = c;
            fa = fc;
        }
        else
        {
            return (fa == 0 ? a : (fb == 0 ? b : c));
        }
    }

    return ((a + b) / 2);
}
