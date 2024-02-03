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
#include "viscosity.h"
#include "func.h"
#include "assert.h"

#define NUMBER 1000

int main()
{
    try
    {
        test::test_random();

        gErrorIgnoreLevel = kWarning;

        double rho{2700}, rho_0{1250}, eta{0.83}, x_1{0.20}, x_2{0.80}, s_t{0.01}, s_x{0.001}, s_r{0.0001};
        std::vector<double> radii{0.005, 0.01};

        for (double radius : radii)
        {
            viscosity visc_all{1, rho, rho_0, eta, radius, x_1, x_2, s_t, s_x, s_r};
            viscosity visc_t{1, rho, rho_0, eta, radius, x_1, x_2, s_t, 0, 0};
            viscosity visc_x{1, rho, rho_0, eta, radius, x_1, x_2, 0, s_x, 0};
            viscosity visc_r{1, rho, rho_0, eta, radius, x_1, x_2, 0, 0, s_r};

            std::vector<double> etas_all, etas_t, etas_x, etas_r;

            for (int i{}; i < NUMBER; i++)
            {
                visc_all.measure();
                visc_all.analysis();
                etas_all.push_back(visc_all.get_η_m());

                visc_r.measure();
                visc_r.analysis();
                etas_r.push_back(visc_r.get_η_m());

                visc_t.measure();
                visc_t.analysis();
                etas_t.push_back(visc_t.get_η_m());
                
                visc_x.measure();
                visc_x.analysis();
                etas_x.push_back(visc_x.get_η_m());
            }

            TH1F hist{"eta", "eta", 50, min(etas_all), max(etas_all)};
            for (double η : etas_all) { hist.Fill(η); }

            TCanvas canvas;
            canvas.cd();
            hist.Draw();
            std::string filepath{"hist/eta_" + std::to_string(radius) + ".png"};
            canvas.SaveAs(filepath.c_str());

            std::cout << "Radius: " << radius << std::endl;
            std::cout << "errors\t" << "η [kg/(m s)]\t" << "σ_h [kg/(m s)]" << std::endl;
            std::cout << "(all):\t" << mean(etas_all) << "\t" << std_dev(etas_all) << std::endl;
            std::cout << "(s_r):\t" << mean(etas_r) << "\t" << std_dev(etas_r) << std::endl;
            std::cout << "(s_t):\t" << mean(etas_t) << "\t" << std_dev(etas_t) << std::endl;
            std::cout << "(s_x):\t" << mean(etas_x) << "\t" << std_dev(etas_x) << std::endl << std::endl;
        }
    }
    catch(const std::exception &e) { std::cerr << e.what() << std::endl; }

    return 0;
}
