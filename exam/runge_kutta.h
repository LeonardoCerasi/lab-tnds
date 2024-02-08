#pragma once

#include "diff_eq.h"

template <size_t N>
class runge_kutta : public differential_equation<N>
{
    public:

        std::array<double, N> step(const double t, const double h, const std::array<double, N> &x, std::function<std::array<double, N> (double, const std::array<double, N> &)> f) const override
        {
            std::array<double, N> k_1{f(t, x)};
            std::array<double, N> k_2{f(t + h/2., x + k_1 * h/2.)};
            std::array<double, N> k_3{f(t + h/2., x + k_2 * h/2.)};
            std::array<double, N> k_4{f(t + h, x + k_3 * h)};

            return (x + (k_1 + 2. * k_2 + 2. * k_3 + k_4) * h / 6.);
        }

        std::array<double, N> integrate(const double t_max, const double h, const std::array<double, N> &x, std::function<std::array<double, N> (double, const std::array<double, N> &)> f)
        {
            std::array<double, N> state{x};
            int n_steps{(int)std::round(t_max / h)};

            double t{};
            for (int i{}; i < n_steps; i++)
            {
                state = step(t, h, state, f);
                t += h;
            }

            return state;
        }
};
