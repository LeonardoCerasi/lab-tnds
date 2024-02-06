#include <iostream>
#include <vector>
#include <string>

#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TError.h"

#include "trapezoidal.h"
#include "bisection.h"

#define prec 1e-4
#define n_int 100

void analysis(double d, double λ, double L, double χ)
{
    TGraph graph;

    trapezoidal integ{};
    bisection zero{};
    auto A{[d, λ, L, &integ] (double x) -> double
            {
                auto f{[d, λ, L, x] (double t) -> double
                        {
                            return std::cos((std::sqrt(L*L + std::pow(x - t, 2)) - std::sqrt(L*L + x*x)) / λ) / d;
                        }};
                return integ.integral(-d/2., d/2., f, prec);
            }};

    double x{-χ}, a{}, x_max{};
    for (int i{}; i <= n_int; i++)
    {
        if (x > 0 && A(x) > a) { x_max = x; }
        
        a = A(x);
        graph.AddPoint(x, A(x));
        x += 2 * χ / n_int;
    }

    double x_0{zero.find_roots(0, x_max, A, 10000, prec)};
    std::cout << "The first zero for λ = " << (int)(λ * std::pow(10, 9)) << " [nm] is at |x| = " << x_0 << " [m]" << std::endl;

    TCanvas canvas;
    canvas.cd();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("ALP");
    std::string title{"lambda = " + std::to_string((int)(λ * std::pow(10, 9))) + " [nm]"};
    graph.SetTitle(title.c_str());
    graph.GetXaxis()->SetTitle("x [m]");
    graph.GetYaxis()->SetTitle("A []");
    std::string name{"graph_" + std::to_string((int)(λ * std::pow(10, 9))) + ".png"};
    canvas.SaveAs(name.c_str());
}

int main()
{
    gErrorIgnoreLevel = kWarning;

    analysis(100e-6, 500e-9, 1, 10e-2);
    analysis(100e-6, 450e-9, 1, 10e-2);
    analysis(100e-6, 400e-9, 1, 10e-2);

    return 0;
}
