#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <array>

#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TError.h"

#include "arr_op.h"
#include "runge_kutta.h"

void analysis(const char *name, double x_0, double y_0, double v_x_0, double v_y_0, double α, double h, double t_max, double constant = 0)
{
    TGraph graph;

    runge_kutta<4> eq;

    std::array<double, 4> state{x_0, y_0, v_x_0, v_y_0};
    auto B{[α, constant](double x, double y) -> double
           { return std::pow(x * x + y * y, -α * 0.5) + constant; }};
    auto f{[B](double t, std::array<double, 4> x) -> std::array<double, 4>
           { return {x.at(2), x.at(3), -B(x.at(0), x.at(1)) * x.at(3), B(x.at(0), x.at(1)) * x.at(2)}; }};

    int n_steps{(int)std::round(t_max / h)};

    double t{}, x{}, y{}, x_p{};
    for (int i{}; i < n_steps; i++)
    {
        x = state.at(0);
        y = state.at(1);
        state = eq.step(t, h, state, f);
        t += h;

        graph.AddPoint(state.at(0), state.at(1));

        if (α == 0 && y < 0 && state.at(1) > 0 && state.at(0) > 0)
        {
            x_p = state.at(0) - state.at(1) * (state.at(0) - x) / (state.at(1) - y);
        }
    }

    if (α == 0)
    {
        std::cout << "After 10 revolutions, the point particle crosses the x-axis at x = " << x_p << " [m]" << std::endl;
        std::cout << "Error with respect to x = 1 [m]: " << std::abs(x_p - 1) << " [m] " << std::endl;
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("ALP");
    std::string title{"alpha = " + std::to_string(α)};
    graph.SetTitle(title.c_str());
    graph.GetXaxis()->SetTitle("x [m]");
    graph.GetYaxis()->SetTitle("y [m]");
    canvas.SaveAs(name);
}

int main()
{
    gErrorIgnoreLevel = kWarning;
    
    analysis("graph_1.png", 1, 0, 0, 1, 0, 0.01, 20 * M_PI);
    analysis("graph_2.png", 1.1, 0, 0, 1, -2, 0.01, 20 * M_PI);
    analysis("graph_3.png", 1.1, 0, 0, 1, 2, 0.01, 20 * M_PI);
    analysis("graph_4.png", 1, 0, 0, 1, 2, 0.01, 20 * M_PI, 1);

    return 0;
}
