#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

#include "TH1F.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TError.h"

#include "random_gen.h"
#include "mc_multi_integral_mean.h"
#include "func.h"
#include "integrals.h"

#define NUMBER 10000

int main()
{
    gErrorIgnoreLevel = kWarning;

    TGraph graph_multi;

    std::vector<int> numbers{100, 500, 1000, 5000, 10000};
    double prec{1e-3};

    multi_integral mc_multi{1};
    auto func{[] (std::vector<double> x) -> double { return (10 + 5 * std::cos(4 * x[1]) * std::sin(7 * x[0]) / std::pow(x[0], 2)); }};
    std::vector<double> a{1, 1};
    std::vector<double> b{2, 2};

    std::vector<double> errors_multi;
    for (int N : numbers)
    {
        TH1F hist_multi{"mc_multi", "mc_multi", 100, 9, 11};

        // if data already present, these are skipped

        integrals_multi(mc_multi, func, a, b, N, NUMBER);
        std::vector<double> integs_multi{read_file("data/log_multi_" + std::to_string(N) + ".dat")};

        //

        for (double i : integs_multi) { hist_multi.Fill(i); }
        errors_multi.push_back(std_dev(integs_multi));

        TCanvas canvas_multi;
        canvas_multi.cd();
        hist_multi.Draw();
        std::string title_multi{"hist/hist_multi_" + std::to_string(N) + ".png"};
        canvas_multi.SaveAs(title_multi.c_str());
    }

    for (int i{}; i < (int)errors_multi.size(); i++) { graph_multi.SetPoint(i, numbers[i], errors_multi[i]);}

    TCanvas canvas_multi;
    canvas_multi.cd();
    canvas_multi.SetLogx();
    canvas_multi.SetLogy();
    graph_multi.Draw();
    canvas_multi.SaveAs("graph_multi.png");

    // σ = k / sqrt(N)

    std::vector<double> k_multi_v{};
    for (int i{}; i < (int)numbers.size(); i++)
    {
        k_multi_v.push_back(errors_multi.at(i) * std::sqrt(numbers.at(i)));
    }
    double k_multi{mean(k_multi_v)};

    std::cout << "In order to obtain σ = " << prec << ", N must be:" << std::endl;
    std::cout << std::fixed << "(multi)\t" << (int)std::pow(k_multi / prec, 2) << std::endl;

    return 0;
}
