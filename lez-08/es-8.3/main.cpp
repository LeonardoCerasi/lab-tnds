#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <array>

#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"

#include "arr_op.h"
#include "runge_kutta.h"
#include "assert.h"

int main()
{
    test::test_array();

    double h{0.001};
    auto osc{[](double t, const std::array<double, 2> &x) -> std::array<double, 2> { return std::array<double, 2>{x[1], -9.80665 * std::sin(x[0])}; }};
    runge_kutta<2> eq;

    std::vector<double> amplitudes;
    std::vector<double> periods;

    for (int i{}; i < 30; i++)
    {
        double t{};
        
        double A{0.1 * (i + 1)};
        double v{};
        std::array<double, 2> x{A, v};

        while (x[1] <= 0)
        {
            v = x[1];
            x = eq.step(t, 0.001, x, osc);
            t += h;
        }

        amplitudes.push_back(A);
        periods.push_back(2 * (t - v * h / (x[1] - v)));
    }

    TGraph graph;
    for (int i{}; i < (int) periods.size(); i++)
    {
        graph.SetPoint(i, amplitudes[i], periods[i]);
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("ALP");
    graph.SetTitle("Pendulum's period of oscillations");
    graph.GetXaxis()->SetTitle("A [rad]");
    graph.GetYaxis()->SetTitle("T [s]");
    canvas.SaveAs("graph_errors.png");

    return 0;
}
