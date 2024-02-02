#include "mc_integral_hm.h"

double mc_int_hm::integral(const std::function<double(double)> func, double a, double b, double f_max, int N, double precision)
{
    if (N < 0) { throw std::invalid_argument("mc_int_hm::integral : number of points must be positive."); }
    if (precision < 0) { throw std::invalid_argument("mc_int_hm::integral : precision must be positive."); }

    int sign{1};
    if (b < a) { double c = a; a = b; b = c; sign = -1; }

    double N_hit{};
    for (int i{}; i < N; i++)
    {
        double x{rand_gen.unif(a, b)};
        double y{rand_gen.unif(0, f_max)};

        if (y < func(x)) { N_hit++; }
    }

    return (sign * f_max * (b - a) * N_hit / (double)N);
}
