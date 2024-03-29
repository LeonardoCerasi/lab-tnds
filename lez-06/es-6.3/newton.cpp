#include "newton.h"

newton::newton(double epsilon) : roots(epsilon) {}

newton::newton(double epsilon, int max_iter) : roots(epsilon, max_iter) {}

// da implementare
double newton::find_roots(double x_min, double x_max, const function &func)
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

        if (sign(fa) * sign(fc) < 0)
        {
            b = c;
            fb = fc;
        }
        else if (sign(fb) * sign(fc) < 0)
        {
            a = c;
            fa = fc;
        }
        else
        {
            return (fa == 0 ? a : (fb == 0 ? b : c));
        }

        n_iter++;
    }

    return ((a + b) / 2);
}
