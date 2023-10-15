#include <iostream>
#include <vector>
#include <stdexcept>

#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"

#include "func.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Correct use of the code: " << argv[0] << " <input_path>." << std::endl;

        return -1;
    }

    char *input_path = argv[1];

    std::vector<double> data;
    try
    {
        data = read_file<double>(input_path);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    TCanvas canvas_1;
    canvas_1.cd();
    TH1F histogram ("charges", "Charge distribution", 100, 0, 20e-19);
    for (int i = 0; i < (int) data.size(); i++)
    {
        histogram.Fill(data[i]);
    }
    histogram.Draw();
    histogram.GetXaxis()->SetTitle("Charge [C]");
    canvas_1.SaveAs("histogram.png");

    TGraph graph; 
    double q_min = 0;
    double s_min = DBL_MAX;

    int counter = 0;
    for (double q = 1.4e-19; q < 1.8e-19; q += 0.001e-19)
    {
        graph.SetPoint(counter, q, S_function(q, data));

        if (S_function(q, data) < s_min)
        {
            s_min = S_function(q, data);
            q_min = q;
        }

        counter++;
    }

    std::cout << "Approximate minimum at q = " << q_min << std::endl;

    TCanvas canvas_2;
    canvas_2.cd();
    graph.Draw();
    graph.SetTitle("Best charge value");
    graph.GetXaxis()->SetTitle("Charge (C)");
    graph.GetYaxis()->SetTitle("S(q) (C^{2})");
    canvas_2.SaveAs("graph.png");

    return 0;
}
