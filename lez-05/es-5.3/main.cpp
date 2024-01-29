#include <iostream>

#include "position.h"
#include "particle.h"
#include "vector_field.h"
#include "point_particle.h"
#include "assert.h"

#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

int main(int argc, char** argv)
{
    test::test_positions();
    test::test_fields();
    
    if (argc != 4)
    {
        std::cerr << "Usage of the programm: " << argv[0] << " <x> <y> <z>" << std::endl;
        return -1;
    }

    position P(atof(argv[1]), atof(argv[2]), atof(argv[3]));

    double d = 1e-10;
    point_particle proton (m_p, e, 0, 0, d/2);
    point_particle electron (m_e, -e, 0, 0, -d/2);
    TGraph graph;

    try
    {
        vector_field E = proton.electric_field(P) + electron.electric_field(P);

        std::cout << "Electric field at the selected point: " << E.get_component(0) << ", " << E.get_component(1) << ", " << E.get_component(2) << std::endl;

        for (int i{100}; i <= 1000; i++)
        {
            position point (0, 0, i * d);
            vector_field elec_field{proton.electric_field(point) + electron.electric_field(point)};
            graph.SetPoint(i-100, i, elec_field.mag());
        }

        double alpha{};
        position P_1{0, 0, 100*d};
        position P_2{0, 0, 1000*d};
        position O{0, 0, 0};
        vector_field E_1{proton.electric_field(P_1) + electron.electric_field(P_1)};
        vector_field E_2{proton.electric_field(P_2) + electron.electric_field(P_2)};
        alpha = log(E_1.mag() / E_2.mag()) / log(P_1.dist(O) / P_2.dist(O));

        std::cout << "Power law with index: " << alpha << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetLogx();
    canvas.SetLogy();
    graph.SetTitle("Dipole electric field");
    graph.Draw("ALP");
    graph.GetXaxis()->SetTitle("z/delta");
    graph.GetYaxis()->SetTitle("E [N/C]");
    canvas.SaveAs("graph.png");

    return 0;
}
