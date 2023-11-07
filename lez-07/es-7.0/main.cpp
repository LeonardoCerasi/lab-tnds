#include <iostream>
#include <iomanip>
#include <cmath>

#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"

#include "midpoint.h"
#include "assert.h"

int main(int argc, char** argv)
{
    test::test_midpoint();

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <n_start> <n_end>" << std::endl;
        return -1;
    }

    int n_start = std::atoi(argv[1]);
    int n_end = std::atoi(argv[2]);

    auto func {[] (double x) -> double { return std::sin(x); }};
    midpoint integ;

    TGraph graph;
    for (int i{n_start}; i < n_end; i++)
    {
        graph.SetPoint((i - n_start), (M_PI / (2 * i)), (integ.integral(0., M_PI, func, i) - 2.));
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetLogx();
    canvas.SetLogy();
    graph.Draw();
    graph.SetTitle("Error of Midpoint numerical integration");
    graph.GetXaxis()->SetTitle("h");
    graph.GetYaxis()->SetTitle("error");
    canvas.SaveAs("graph.png");

    return 0;
}
