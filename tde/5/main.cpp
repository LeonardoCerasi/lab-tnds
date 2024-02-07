#include <iostream>
#include <vector>
#include <cmath>

#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TError.h"

#include "random_gen.h"
#include "capacitor.h"
#include "func.h"

#define N 10000

double simulate(double V_0, double V_1, double C, double R, double p_V_0, double p_V_1, double p_R, double p_t)
{
    capacitor cap{V_0, V_1, C, R, p_V_0, p_V_1, p_R, p_t};

    std::vector<double> capacity{};

    for (int i{}; i < N; i++)
    {
        cap.measure();
        cap.analysis();
        
        capacity.push_back(cap.get_C());
    }

    return std_dev(capacity) / mean(capacity);
}

int main()
{
    double C{2e-6}, R{100e3}, V_0{12}, V_1{3}, p{0.03};

    ////////////////////////////////////////////////////////////////

    double p_C{simulate(V_0, V_1, C, R, p, p, p, p)};

    std::cout << "e_C: " << p_C << std::endl << std::endl;

    ////////////////////////////////////////////////////////////////

    double p_C_V_0{simulate(V_0, V_1, C, R, p, 0, 0, 0)};
    double p_C_V_1{simulate(V_0, V_1, C, R, 0, p, 0, 0)};
    double p_C_R{simulate(V_0, V_1, C, R, 0, 0, p, 0)};
    double p_C_t{simulate(V_0, V_1, C, R, 0, 0, 0, p)};

    std::cout << "e_C (V_0): " << p_C_V_0 << std::endl;
    std::cout << "e_C (V_1): " << p_C_V_1 << std::endl;
    std::cout << "e_C (R):   " << p_C_R << std::endl;
    std::cout << "e_C (t):   " << p_C_t << std::endl;

    ////////////////////////////////////////////////////////////////

    gErrorIgnoreLevel = kWarning;

    TGraph graph;

    double p_1{0.02}, p_2{0.07};
    int n{100};
    std::vector<double> perc_C{};

    double perc{p_1};
    for (int i{}; i <= n; i++)
    {
        perc_C.push_back(simulate(V_0, V_1, C, R, perc, perc, p, p));
        graph.AddPoint(perc, perc_C.at(i));
        perc += (p_2 - p_1) / n;
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetGridx();
    canvas.SetGridy();
    graph.Draw("ALP");
    graph.SetTitle("sigma_C");
    graph.GetXaxis()->SetTitle("p [%]");
    graph.GetYaxis()->SetTitle("p_C [%]");
    canvas.SaveAs("graph.png");

    ////////////////////////////////////////////////////////////////

    double p_wanted{0.07};

    // rapid method

    double m{(perc_C.at(n) - perc_C.at(0)) / (p_2 - p_1)};
    double p_V{p_1 + (p_wanted - perc_C.at(0)) / m};

    std::cout << "\n(rapid)   In order to have e_C = " << p_wanted << ", e_V must be " << p_V << std::endl;

    // complex method

    double e_1{}, e_2{}, e_C_1{}, e_C_2{};
    for (int i{}; i < n; i++)
    {
        if (perc_C.at(i) <= p_wanted && perc_C.at(i + 1) >= p_wanted)
        {
            e_1 = p_1 + i * (p_2 - p_1) / n;
            e_2 = e_1 + (p_2 - p_1) / n;
            e_C_1 = perc_C.at(i);
            e_C_2 = perc_C.at(i + 1);

            break;
        }
    }

    double m_complex{(e_C_2 - e_C_1) / (e_2 - e_1)};
    double p_V_complex{e_1 + (p_wanted - e_C_1) / m_complex};

    std::cout << "\n(complex) In order to have e_C = " << p_wanted << ", e_V must be " << p_V_complex << std::endl;

    return 0;
}
