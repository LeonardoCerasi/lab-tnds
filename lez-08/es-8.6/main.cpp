#include <iostream>
#include <cmath>
#include <array>

#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TError.h"

#include "arr_op.h"
#include "runge_kutta.h"
#include "assert.h"

#define Q -1.60217653e-19 // C
#define M 9.1093826e-31 // kg

int main()
{
    test::test_array();
    test::test_runge_kutta();

    gErrorIgnoreLevel = kWarning;

    TGraph graph;
    runge_kutta<6> rk;

    std::array<double, 3> B{0., 0., 5e-3};
    std::array<double, 3> E{0., 0., 0.};
    std::array<double, 6> x{0., 0., 0., 8e6, 0., 0.};

    auto f{[&B, &E](double t, const std::array<double, 6> &x) -> std::array<double, 6>
           {
               return std::array<double, 6>{
                   x[3],
                   x[4],
                   x[5],
                   (Q / M) * (x[4] * B[2] - x[5] * B[1] + E[0]),
                   (Q / M) * (x[5] * B[0] - x[3] * B[2] + E[1]),
                   (Q / M) * (x[3] * B[1] - x[4] * B[0] + E[2])
               };
           }};
    
    double t_max{1e-8};
    double h{1e-12};
    int n_steps{(int) std::lround(t_max / h)};

    double t{};
    for (int i{}; i < n_steps; i++)
    {
        graph.SetPoint(i, x[0], x[1]);

        x = rk.step(t, h, x, f);
        t += h;
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("ALP");
    graph.SetTitle("Electrons's orbit");
    graph.GetXaxis()->SetTitle("x [m]");
    graph.GetYaxis()->SetTitle("y [m]");
    canvas.SaveAs("graph.png");

    //////////////

    TGraph graph_2;

    B = {0., 0., 5e-3};
    E = {1e4, 0., 0.};
    x = {0., 0., 0., 8e6, 0., 0.};

    t_max = 5e-8;
    h = 1e-12;
    n_steps = (int) std::lround(t_max / h);

    t = 0.;
    for (int i{}; i < n_steps; i++)
    {
        graph_2.SetPoint(i, x[0], x[1]);

        x = rk.step(t, h, x, f);
        t += h;
    }

    TCanvas canvas_2;
    canvas_2.cd();
    canvas_2.SetGridx();
    canvas_2.SetGridy();
    graph_2.Draw("ALP");
    graph_2.SetTitle("Electrons's orbit");
    graph_2.GetXaxis()->SetTitle("x [m]");
    graph_2.GetYaxis()->SetTitle("y [m]");
    canvas_2.SaveAs("graph_e.png");

    return 0;
}
