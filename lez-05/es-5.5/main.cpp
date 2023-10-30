#include <iostream>
#include <vector>
#include <cmath>
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"

#include "position.h"
#include "particle.h"
#include "vector_field.h"
#include "point_particle.h"
#include "spherical_body.h"
#include "assert.h"

int main(int argc, char** argv)
{
    test::test_positions();
    test::test_fields();
    
    double delta{10e3};
    double d{2.5e5};
    double r{1e3};
    double m{3e12};

    double phi_goce{std::asin(delta / (r_t + d))};
    double phi_mount{std::asin(r / (r_t + r))};

    spherical_body earth (m_t, r_t);
    std::vector<spherical_body> mountains;
    position goce('s', r_t + d, 0., M_PI_2);
    std::vector<vector_field> grav_field;

    double earth_field = earth.gravitational_field(goce).mag();
    std::cout << "The ideal Earth's gravitational field at GOCE orbit is " << earth_field << " N/kg." << std::endl;

    TGraph graph;

    try
    {
        for (int i{}; i < 100; i++)
        {
            spherical_body mount(m, r, 's', r_t + r, M_PI_2 + i * phi_mount, M_PI_2);
            mountains.push_back(mount);
        }

        for (int i{}; i < std::floor(2 * M_PI / phi_goce); i++)
        {
            double phi = goce.get_coordinate('s', 1);
            goce.set_coordinate('s', 1, phi + phi_goce);
            
            vector_field G (goce);
            for (spherical_body mount : mountains)
            {
                G += mount.gravitational_field(goce);
            }

            graph.SetPoint(i, G.get_coordinate('s', 1), G.mag() / earth_field);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    TCanvas canvas("canvas", "Gravitational field");
    canvas.cd();
    canvas.SetLogy();
    graph.SetTitle("Gravitational field");
    graph.Draw("ALP");
    graph.GetXaxis()->SetTitle("Polar angle phi [rad]");
    graph.GetYaxis()->SetTitle("delta_g / g");
    canvas.SaveAs("graph.png");

    return 0;
}
