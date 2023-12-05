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
#include "func.h"
#include "assert.h"

int main()
{
    test::test_array();
    test::test_runge_kutta();

    TGraph graph;

    double h{0.001};
    double delta{0.05};
    int n_delta{(int)lround((11. - 9.) / delta)};

    double w_0{10.};
    double a{1 / 30.};
    double a_0{1.};
    double w{9.};
    
    std::array<double, 2> x{0., 0.};
    runge_kutta<2> eq;

    std::vector<double> omega;
    std::vector<double> amplitudes;

    for (int i{}; i <= n_delta; i++)
    {
        w = 9. + i * delta;
        auto osc{[&w_0, &a, &a_0, &w](double t, const std::array<double, 2> &x) -> std::array<double, 2>
                 { return std::array<double, 2>{x[1], -std::pow(w_0, 2) * x[0] - a * x[1] + a_0 * std::sin(w * t)}; }};

        std::vector<double> time;
        std::vector<double> position;
        std::vector<double> velocity;

        double t_max{30. / a};
        int n_steps{(int)lround(t_max / h)};

        double t{};
        for (int i{}; i < n_steps; i++)
        {
            time.push_back(t);
            position.push_back(x[0]);
            velocity.push_back(x[1]);

            x = eq.step(t, h, x, osc);
            t += h;
        }

        double amplitude{find_amplitude(time, position, velocity, t_max / 2., h)};
        std::cout << w << "\t\t" << amplitude << "\n\n" << std::endl;

        omega.push_back(w);
        amplitudes.push_back(amplitude);
    }

    for (int i{}; i < (int) amplitudes.size(); i++)
    {
        graph.SetPoint(i, omega[i], amplitudes[i]);
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("aLP");
    graph.SetTitle("Resonance");
    graph.GetXaxis()->SetTitle("omega [rad/s]");
    graph.GetYaxis()->SetTitle("A [m]");
    canvas.SaveAs("graph_resonace.png");

    return 0;
}
