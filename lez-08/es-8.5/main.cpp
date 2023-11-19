#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <array>

#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TError.h"

#include "arr_op.h"
#include "runge_kutta.h"
#include "func.h"
#include "assert.h"

#define G    6.6742e-11      // m^3 kg^-1 s^-2
#define M_S  1.988441030e30  // kg
#define M_T  5.9722e24       // kg
#define D_P  1.47098074e11   // m
#define V_P  3.0287e4        // m s^-1
#define Y    3.1536e7        // s

int main()
{
    test::test_array();
    test::test_runge_kutta();

    gErrorIgnoreLevel = kWarning;

    TGraph graph;
    runge_kutta<4> eq;

    std::array<double, 4> x{D_P, 0., 0., V_P};
    auto grav { [] (double t, const std::array<double, 4> &x) -> std::array<double, 4>
    {
        double grav_field { -(G * M_S / std::pow((std::pow(x[0], 2) + std::pow(x[1], 2)), 1.5)) };
        return (std::array<double, 4> { x[2], x[3], grav_field * x[0], grav_field * x[1] });
    } };

    std::vector<double> periods;
    double period{};

    double t_max { 3. * Y };
    double h{10.};
    int n_steps { (int) std::lround((t_max) / h) };

    double t{};
    for (int i{}; i < n_steps; i++)
    {
        graph.SetPoint(i, x[0], x[1]);

        x = eq.step(t, h, x, grav);
        t += h;

        if (std::fabs(x[0] - D_P) < 0.1)
        {
            period = t - period;
            periods.push_back(period);
        }
    }

    period = 0.;
    for (int i{}; i < (int) periods.size(); i++) { period += periods[i] / periods.size(); }

    std::cout << "Earth's orbital period: " << period << " [s] = " << (period / Y) << "[y]" << std::endl;
    std::cout << "Error: " << (Y - period) << "[s] = " << (Y - period) / 3600 << "[h]" << std::endl;

    TCanvas canvas;
    canvas.cd();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("ALP");
    graph.SetTitle("Earth's orbit");
    graph.GetXaxis()->SetTitle("x [m]");
    graph.GetYaxis()->SetTitle("y [m]");
    canvas.SaveAs("graph.png");

    /////////////////

    TGraph graph_a;
    runge_kutta<4> eq_a;

    double a{5e41};
    std::array<double, 4> x_a{D_P, 0., 0., V_P};
    auto grav_a{[&a] (double t, const std::array<double, 4> &x) -> std::array<double, 4>
    {
        double grav_field { -(G * M_S / std::pow((std::pow(x[0], 2) + std::pow(x[1], 2)), 1.5)) - (a / std::pow((std::pow(x[0], 2) + std::pow(x[1], 2)), 2.5)) };
        return (std::array<double, 4> { x[2], x[3], grav_field * x[0], grav_field * x[1] });
    }};

    double t_max_a { 30. * Y };
    double h_a{100.};
    int n_steps_a { (int) std::lround((t_max_a) / h_a) };

    double t_a{};
    for (int i{}; i < n_steps_a; i++)
    {
        graph_a.SetPoint(i, x_a[0], x_a[1]);

        x_a = eq_a.step(t_a, h_a, x_a, grav_a);
        t_a += h_a;
    }

    TCanvas canvas_a;
    canvas_a.cd();
    canvas_a.SetGridx();
    canvas_a.SetGridy();
    graph_a.Draw("ALP");
    graph_a.SetTitle("Earth's orbit + perturbation");
    graph_a.GetXaxis()->SetTitle("x [m]");
    graph_a.GetYaxis()->SetTitle("y [m]");
    canvas_a.SaveAs("graph_a.png");

    return 0;
}
