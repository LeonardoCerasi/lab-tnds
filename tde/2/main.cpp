#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <array>

#include "arr_op.h"
#include "runge_kutta.h"
#include "random_gen.h"
#include "func.h"

double simulate(double t, double h, const std::array<double, 2> &x, std::function<std::array<double, 2>(double, const std::array<double, 2> &)> f, int n_iter, double σ_v)
{
    runge_kutta<2> eq;
    random_gen rand_gen{1};
    std::vector<double> positions{};

    for (int i{}; i < n_iter; i++)
    {
        std::array<double, 2> perturbation{0, rand_gen.gauss_bm(x.at(1), σ_v)};
        positions.push_back(eq.integrate(t, h, x + perturbation, f).at(0));
    }

    return std_dev(positions);
}

int main()
{
    runge_kutta<2> eq;
    
    std::array<double, 2> state{1, 0};
    double ω{1.15}, α{0.01};
    auto f{[ω, α] (double t, std::array<double, 2> x) -> std::array<double, 2> { return {x.at(1), -ω*ω * x.at(0) - α * x.at(1)};}};

    double t_max{43.};
    double h{0.1};

    double Δ_h{std::fabs(eq.integrate(t_max, h, state, f).at(0) - eq.integrate(t_max, h / 2, state, f).at(0))};
    double ε{(16. / 15.) * Δ_h};

    std::cout << "Integration with h = " << h << " [s] results in x = " << eq.integrate(t_max, h, state, f).at(0) << " ± " << ε << " [m]" << std::endl;

    // ε = k * h^4 = Δ * 16/15
    double ε_μ{50e-6};
    double h_μ{std::pow(ε_μ * (15. / 16.) * std::pow(h, 4) / Δ_h, 1./4.)};

    std::cout << "\nIn order to have ε = " << ε_μ << " [m], h must be " << h_μ << " [s]" << std::endl;

    int N{10000};

    double σ_v{3e-3};
    std::cout << "\nWith σ_v = " << σ_v << " [m/s] and N = " << N << ", the standard deviation of final positions is σ = " << simulate(t_max, h_μ, state, f, N, σ_v) << " [m]" << std::endl;

    std::cout << "\nStandard deviation ad a function of σ_v:" << std::endl;
    std::cout << "σ_v [m/s]\t" << "σ [m]" << std::endl;
    std::vector<double> sigmas{3e-3, 5e-3, 8e-3, 12e-3, 15e-3};
    for (double σ : sigmas)
    {
        std::cout << σ << "\t\t" << simulate(t_max, h_μ, state, f, N, σ) << std::endl;
    }


    return 0;
}
