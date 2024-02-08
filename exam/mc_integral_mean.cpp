#include "mc_integral_mean.h"

double mc_int_mean::integral(const std::function<double(double)> func, double a, double b, int N)
{
    if (N < 0) { throw std::invalid_argument("mc_int_mean::integral : number of points must be positive."); }

    int sign{1};
    if (b < a) { double c = a; a = b; b = c; sign = -1; }

    std::vector<double> rand_num;
    for (int i{}; i < N; i++) { rand_num.push_back(rand_gen.unif(a, b)); }

    double integ{};
    for (double x : rand_num) { integ += func(x); }

    return (sign * integ * (b - a) / (double)N);
}
