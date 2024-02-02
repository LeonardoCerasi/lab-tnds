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
#include "mc_integral_mean.h"
#include "mc_integral_hm.h"
#include "assert.h"
#include "func.h"
#include "integrals.h"

#define NUMBER 10000

int main()
{
    test::test_random();

    gErrorIgnoreLevel = kWarning;

    TGraph graph_mean;
    TGraph graph_hm;

    std::vector<int> numbers{100, 500, 1000, 5000, 10000, 50000, 100000};
    double prec{1e-3};

    mc_int_mean mc_mean{1};
    mc_int_hm mc_hm{1};
    auto func{[] (double x) -> double { return std::sin(x); }};

    std::vector<double> errors_mean;
    std::vector<double> errors_hm;
    for (int N : numbers)
    {
        TH1F hist_mean{"mc_mean", "mc_mean", 100, 0, 4};
        TH1F hist_hm{"mc_hm", "mc_hm", 100, 0, 4};

        // if data already present, these are skipped

        integrals_mean(mc_mean, func, 0, M_PI, 1, N, prec, NUMBER);
        std::vector<double> integs_mean{read_file("data/log_mean_" + std::to_string(N) + ".dat")};

        integrals_hm(mc_hm, func, 0, M_PI, 1, N, prec, NUMBER);
        std::vector<double> integs_hm{read_file("data/log_hm_" + std::to_string(N) + ".dat")};

        //

        for (double i : integs_mean) { hist_mean.Fill(i); }
        errors_mean.push_back(std_dev(integs_mean));

        for (double i : integs_hm) { hist_hm.Fill(i); }
        errors_hm.push_back(std_dev(integs_hm));

        TCanvas canvas_mean;
        canvas_mean.cd();
        hist_mean.Draw();
        std::string title_mean{"hist/hist_mean_" + std::to_string(N) + ".png"};
        canvas_mean.SaveAs(title_mean.c_str());

        TCanvas canvas_hm;
        canvas_hm.cd();
        hist_hm.Draw();
        std::string title_hm{"hist/hist_hm_" + std::to_string(N) + ".png"};
        canvas_hm.SaveAs(title_hm.c_str());
    }

    for (int i{}; i < (int)errors_mean.size(); i++) { graph_mean.SetPoint(i, numbers[i], errors_mean[i]); }
    for (int i{}; i < (int)errors_hm.size(); i++) { graph_hm.SetPoint(i, numbers[i], errors_hm[i]); }

    TCanvas canvas_mean;
    canvas_mean.cd();
    canvas_mean.SetLogx();
    canvas_mean.SetLogy();
    graph_mean.Draw();
    canvas_mean.SaveAs("graph_mean.png");

    TCanvas canvas_hm;
    canvas_hm.cd();
    canvas_hm.SetLogx();
    canvas_hm.SetLogy();
    graph_hm.Draw();

    // σ = k / sqrt(N)

    std::vector<double> k_mean_v{};
    std::vector<double> k_hm_v{};
    for (int i{}; i < (int)numbers.size(); i++)
    {
        k_mean_v.push_back(errors_mean.at(i) * std::sqrt(numbers.at(i)));
        k_hm_v.push_back(errors_hm.at(i) * std::sqrt(numbers.at(i)));
    }
    double k_mean{mean(k_mean_v)};
    double k_hm{mean(k_hm_v)};

    std::cout << "In order to obtain σ = " << prec << ", N must be:" << std::endl;
    std::cout << std::fixed << "(mean)\t" << (int)std::pow(k_mean / prec, 2) << std::endl;
    std::cout << std::fixed << "(hm)\t" << (int)std::pow(k_hm / prec, 2) << std::endl;

    return 0;
}
