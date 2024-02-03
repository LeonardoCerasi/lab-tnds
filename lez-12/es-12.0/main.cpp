#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TError.h"

#include "random_gen.h"
#include "prism.h"
#include "func.h"
#include "assert.h"

#define NUMBER 10000

int main()
{
    try
    {
        test::test_random();

        gErrorIgnoreLevel = kWarning;

        std::vector<double> theta_0_v, theta_1_v, theta_2_v;
        std::vector<double> delta_1_v, delta_2_v;
        std::vector<double> n_1_v, n_2_v;
        std::vector<double> A_v, B_v;

        prism experiment{1, 579.1, 404.7, M_PI / 3., 0.3e-3, 2.7, 60000, M_PI / 2.};

        for (int i{}; i < NUMBER; i++)
        {
            experiment.measures();
            experiment.analysis();

            theta_0_v.push_back(experiment.get_theta_0_m());
            theta_1_v.push_back(experiment.get_theta_1_m());
            theta_2_v.push_back(experiment.get_theta_2_m());

            delta_1_v.push_back(experiment.get_delta_1_m());
            delta_2_v.push_back(experiment.get_delta_2_m());

            n_1_v.push_back(experiment.get_n_1_m());
            n_2_v.push_back(experiment.get_n_2_m());

            A_v.push_back(experiment.get_A_m());
            B_v.push_back(experiment.get_B_m());
        }

        std::cout << "Expected results:\n"
                  << std::endl;

        std::cout << std::fixed << std::setprecision(6) << "theta_0: " << mean(theta_0_v) << " ± " << std_dev(theta_0_v) << " [rad]" << std::endl;
        std::cout << std::fixed << std::setprecision(6) << "theta_1: " << mean(theta_1_v) << " ± " << std_dev(theta_1_v) << " [rad]" << std::endl;
        std::cout << std::fixed << std::setprecision(6) << "theta_2: " << mean(theta_2_v) << " ± " << std_dev(theta_2_v) << " [rad]" << std::endl << std::endl;

        std::cout << std::fixed << std::setprecision(6) << "delta_1: " << mean(delta_1_v) << " ± " << std_dev(delta_1_v) << " [rad]" << std::endl;
        std::cout << std::fixed << std::setprecision(6) << "delta_2: " << mean(delta_2_v) << " ± " << std_dev(delta_2_v) << " [rad]" << std::endl;
        std::cout << std::fixed << std::setprecision(6) << "corr. coeff.: " << corr(delta_1_v, delta_2_v) << std::endl << std::endl;

        std::cout << std::fixed << std::setprecision(6) << "n_1: " << mean(n_1_v) << " ± " << std_dev(n_1_v) << std::endl;
        std::cout << std::fixed << std::setprecision(6) << "n_2: " << mean(n_2_v) << " ± " << std_dev(n_2_v) << std::endl;
        std::cout << std::fixed << std::setprecision(6) << "corr. coeff.: " << corr(n_1_v, n_2_v) << std::endl << std::endl;

        std::cout << std::fixed << std::setprecision(6) << "A: " << mean(A_v) << " ± " << std_dev(A_v) << std::endl;
        std::cout << std::fixed << std::setprecision(6) << "B: " << mean(B_v) << " ± " << std_dev(B_v) << " [nm²]" << std::endl;
        std::cout << std::fixed << std::setprecision(6) << "corr. oceff.: " << corr(A_v, B_v) << std::endl;

        // histograms

        double perc_min{1}, perc_max{1};
        TH1F theta_0{"theta_0", "theta_0", 100, min(theta_0_v) * perc_min, max(theta_0_v) * perc_max};
        TH1F theta_1{"theta_1", "theta_1", 100, min(theta_1_v) * perc_min, max(theta_1_v) * perc_max};
        TH1F theta_2{"theta_2", "theta_2", 100, min(theta_2_v) * perc_min, max(theta_2_v) * perc_max};

        TH1F delta_1{"delta_1", "delta_1", 100, min(delta_1_v) * perc_min, max(delta_1_v) * perc_max};
        TH1F delta_2{"delta_2", "delta_2", 100, min(delta_1_v) * perc_min, max(delta_2_v) * perc_max};
        TH2F delta{"delta", "delta", 100, min(delta_1_v) * perc_min, max(delta_1_v) * perc_max, 100, min(delta_2_v) * perc_min, max(delta_2_v) * perc_max};

        TH1F n_1{"n_1", "n_1", 100, min(n_1_v) * perc_min, max(n_1_v) * perc_max};
        TH1F n_2{"n_2", "n_2", 100, min(n_2_v) * perc_min, max(n_2_v) * perc_max};
        TH2F n{"n", "n", 100, min(n_1_v) * perc_min, max(n_1_v) * perc_max, 100, min(n_2_v) * perc_min, max(n_2_v) * perc_max};

        TH1F A{"A", "A", 100, min(A_v) * perc_min, max(A_v) * perc_max};
        TH1F B{"B", "B", 100, min(B_v) * perc_min, max(B_v) * perc_max};
        TH2F AB{"AB", "deltAB", 100, min(A_v) * perc_min, max(A_v) * perc_max, 100, min(B_v) * perc_min, max(B_v) * perc_max};

        for (int i{}; i < NUMBER; i++)
        {
            theta_0.Fill(theta_0_v[i]);
            theta_1.Fill(theta_1_v[i]);
            theta_2.Fill(theta_2_v[i]);

            delta_1.Fill(delta_1_v[i]);
            delta_2.Fill(delta_2_v[i]);
            delta.Fill(delta_1_v[i], delta_2_v[i]);

            n_1.Fill(n_1_v[i]);
            n_2.Fill(n_2_v[i]);
            n.Fill(n_1_v[i], n_2_v[i]);

            A.Fill(A_v[i]);
            B.Fill(B_v[i]);
            AB.Fill(A_v[i], B_v[i]);
        }

        TCanvas theta_canvas_0;
        theta_canvas_0.cd();
        theta_0.Draw();
        theta_canvas_0.SaveAs("hist/theta_0_hist.png");
        TCanvas theta_canvas_1;
        theta_canvas_1.cd();
        theta_1.Draw();
        theta_canvas_1.SaveAs("hist/theta_1_hist.png");
        TCanvas theta_canvas_2;
        theta_canvas_2.cd();
        theta_2.Draw();
        theta_canvas_2.SaveAs("hist/theta_2_hist.png");

        TCanvas delta_canvas_1;
        delta_canvas_1.cd();
        delta_1.Draw();
        delta_canvas_1.SaveAs("hist/delta_1_hist.png");
        TCanvas delta_canvas_2;
        delta_canvas_2.cd();
        delta_2.Draw();
        delta_canvas_2.SaveAs("hist/delta_2_hist.png");
        TCanvas delta_canvas;
        delta_canvas.cd();
        delta.Draw();
        delta_canvas.SaveAs("hist/delta_hist.png");

        TCanvas n_canvas_1;
        n_canvas_1.cd();
        n_1.Draw();
        n_canvas_1.SaveAs("hist/n_1_hist.png");
        TCanvas n_canvas_2;
        n_canvas_2.cd();
        n_2.Draw();
        n_canvas_2.SaveAs("hist/n_2_hist.png");
        TCanvas n_canvas;
        n_canvas.cd();
        n.Draw();
        n_canvas.SaveAs("hist/n_hist.png");

        TCanvas cauchy_canvas_a;
        cauchy_canvas_a.cd();
        A.Draw();
        cauchy_canvas_a.SaveAs("hist/cauchy_a_hist.png");
        TCanvas cauchy_canvas_b;
        cauchy_canvas_b.cd();
        B.Draw();
        cauchy_canvas_b.SaveAs("hist/cauchy_b_hist.png");
        TCanvas cauchy_canvas;
        cauchy_canvas.cd();
        AB.Draw();
        cauchy_canvas.SaveAs("hist/cauchy_hist.png");
    }
    catch(const std::exception &e) { std::cerr << e.what() << std::endl; }
    

    return 0;
}
