#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <functional>

#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TError.h"

#include "mc_integral_mean.h"
#include "simpson.h"
#include "runge_kutta.h"
#include "arr_op.h"

int main()
{
    auto f{[] (double t) -> double { return std::pow(std::cos(t), 2) / std::sqrt(2 + t*t); }};
    double a{M_PI_4};
    double ε{1e-10};

    // 1 ////////////////////////////////////////////////////////////////////////////////////////

    simpson simp{};
    // σ = k * h^4, therefor I_h - I = k * h^4 and I_(h/2) - I = k * (h/2)^4, so |I_h - I_(h/2)| = k * h^4 * (15/16), h = a/N
    double n{1000}; // test N to estimate k
    double k_simp{(16. / 15.) * std::fabs(simp.integral(0, a, f, n) - simp.integral(0, a, f, 2 * n)) / std::pow(a / n, 4)};
    
    int N{(int)std::round(a / std::pow(ε / k_simp, 0.25))};
    double int_simp{simp.integral(0, a, f, N)};

    std::cout << "In order to have an error ε = " << ε << " with Simpson's method, N must be " << N << " (h = " << std::scientific << std::setprecision(3) << (a / N) << ")" << std::endl;
    std::cout << "The integral calculated with Simpson's method (N found before) is: " << std::fixed << std::setprecision(10) << int_simp << std::endl;

    // 2 ////////////////////////////////////////////////////////////////////////////////////////

    mc_int_mean mean_int{1};
    double int_mean{mean_int.integral(f, 0, a, N)};
    double err_mean{std::fabs(int_simp - int_mean)};

    std::cout << "\nThe integral calculated with Mean method (N found before) is: " << std::fixed << std::setprecision(10) << int_mean << std::endl;
    std::cout << "Error (with respect to Simpson's method): " << std::fixed << std::setprecision(10) << err_mean << std::endl;

    // 3 ////////////////////////////////////////////////////////////////////////////////////////

    // σ = k * a / sqrt(N), therefor k = σ * sqrt(N) / a and N = (k * a / σ)^2
    double k_mean{err_mean * std::sqrt(N) / a};
    double N_mean{std::pow(k_mean * a / ε, 2)};

    std::cout << std::scientific << "In order to have an error ε = " << std::setprecision(0) << ε << " with Mean method, N must be " << std::setprecision(3) << N_mean << std::endl;

    // 4 ////////////////////////////////////////////////////////////////////////////////////////

    auto vec_f{[f] (double t, std::array<double, 1> x) -> std::array<double, 1> { return {f(t)};}};
    std::array<double, 1> state{0};
    runge_kutta<1> rk;

    // σ = k * h^4, therefor I_h - I = k * h^4 and I_(h/2) - I = k * (h/2)^4, so |I_h - I_(h/2)| = k * h^4 * (15/16), h = a/N
    double h{1e-5}; // test h to estimate k
    double Δ_h{std::fabs(rk.integrate(a, h, state, vec_f).at(0) - rk.integrate(a, h / 2., state, vec_f).at(0))};
    double k_rk{(16. / 15.) * Δ_h / std::pow(h, 4)};

    double h_rk{std::pow(ε / k_rk, 0.25)};
    double int_rk{rk.integrate(a, h_rk, state, vec_f).at(0)};

    std::cout << std::setprecision(0) << "\nIn order to have an error ε = " << ε << " with Runge-Kutta's method, h must be " << std::setprecision(3) << h_rk << " (N = " << std::fixed << std::setprecision(0) << std::round(a / h_rk) << ")" << std::endl;
    std::cout << "The integral calculated with Runge-Kutta's method (h found before) is: " << std::setprecision(10) << int_rk << std::endl;

    std::cout << "\nNon ha precisione ε ???" << std::endl;

    // 5 ////////////////////////////////////////////////////////////////////////////////////////

    gErrorIgnoreLevel = kWarning;

    TGraph graph;

    std::vector<int> N_v{10, 50, 100, 500, 1000, 5000, 10000};

    std::cout << "\nError of Simpson's method with respect to Runke-Kutta's method as a function of N:" << std::endl;
    std::cout << "N\t|I_rk - I_simp(N)|" << std::endl;
    for (int n_simp : N_v)
    {
        graph.AddPoint(a/n_simp, std::fabs(int_rk - simp.integral(0, a, f, n_simp)));
        std::cout << n_simp << "\t" << std::scientific << std::setprecision(10) << std::fabs(int_rk - simp.integral(0, a, f, n_simp)) << std::endl;
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetLogx();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("ALP");
    graph.SetTitle("I_rk - I_simp");
    graph.GetXaxis()->SetTitle("h = a / N");
    graph.GetYaxis()->SetTitle("|I_rk - I_simp(h)|");
    canvas.SaveAs("graph.png");

    return 0;
}
