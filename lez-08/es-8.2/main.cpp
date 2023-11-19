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
    test::test_runge_kutta();

    std::vector<double> steps;
    std::vector<double> errors;

    std::vector<double> fractions {10., 5., 2.5};
    for (int e{2}; e <= 5; e++)
    {
        for (double fract : fractions)
        {
            double t_max{70.};
            std::array<double, 2> x{0., 1.};
            auto osc{[](double t, const std::array<double, 2> &x) -> std::array<double, 2> { return std::array<double, 2>{x[1], -x[0]}; }};
            runge_kutta<2> eq;
            TGraph graph_h;

            double t{};
            double h{fract * std::pow(10, -e)};
            int n_steps{(int)lround(t_max / h)};

            for (int i{}; i < n_steps; i++)
            {
                graph_h.SetPoint(i, t, x[0]);

                x = eq.step(t, h, x, osc);
                t += h;
            }

            steps.push_back(h);
            errors.push_back(std::fabs(x[0] - std::sin(t_max)));

            // TCanvas canva;
            // canva.cd();
            // canva.SetGridx();
            // canva.SetGridy();
            // graph_h.Draw("ALP");
            // std::string title{"Harmonic oscillator (h = " + std::to_string(h) + " s)"};
            // graph_h.SetTitle(title.c_str());
            // graph_h.GetXaxis()->SetTitle("t [s]");
            // graph_h.GetYaxis()->SetTitle("x [m]");
            // title = "graph_" + std::to_string(h) + ".png";
            // canva.SaveAs(title.c_str());
        }
    }

    TGraph graph;
    for (int i{}; i < (int) errors.size(); i++)
    {
        std::cout << steps[i] << "\t" << errors[i] << std::endl;
        graph.SetPoint(i, steps[i], errors[i]);
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetLogx();
    canvas.SetLogy();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("ALP");
    graph.SetTitle("Runge-Kutta method's error");
    graph.GetXaxis()->SetTitle("h [s]");
    graph.GetYaxis()->SetTitle("error [m]");
    canvas.SaveAs("graph_errors.png");

    return 0;
}
