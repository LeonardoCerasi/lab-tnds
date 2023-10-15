#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

#include "func.h"
#include "pos.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Correct use of the code: " << argv[0] << " <input_path> <output_path>." << std::endl;

        return -1;
    }

    char *input_path = argv[1];
    char *output_path = argv[2];

    std::vector<Position> data;
    try
    {
        data = initialize_pos(read_file(input_path));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    best_path(data, Position());

    std::ofstream output (output_path);
    for (Position p : data)
    {
        output << p.get_x() << " , " << p.get_y() << " . " << p.get_z() << std::endl;
    }
    output.close();

    TCanvas canvas;
    canvas.cd();
    TGraph graph;
    graph.SetPoint(0, 0, 0);
    int counter = 1;
    for (std::vector<Position>::iterator it = data.begin(); it != data.end(); it++)
    {
        graph.SetPoint(counter, it->get_x(), it->get_y());
        counter++;
    }

    // per qualche motivo rompe il grafico
    // graph.GetXaxis()->SetLimits(-10, -10);
    graph.SetMinimum(-10);
    graph.SetMaximum(10);
    graph.GetXaxis()->SetTitle("X");
    graph.GetYaxis()->SetTitle("Y");
    graph.SetTitle("Shortest path");
    graph.Draw();
    canvas.SaveAs("graph.png");

    return 0;
}
