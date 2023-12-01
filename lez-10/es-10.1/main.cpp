#include <iostream>
#include <string>

#include "TH1F.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"

#include "random_gen.h"
#include "assert.h"
#include "func.h"

#define N 1*2*3*4*5*6*7*8*9*11

int main()
{
    test::test_random();

    TGraph graph_sigma;
    random_gen rand_gen{1};
    
    std::vector<double> rand_num;
    for (int i{}; i < N; i++) { rand_num.push_back(rand_gen.random()); }
    
    for (int n{1}; n <= 12; n++)
    {
        std::vector<double> sums = sum_elements(rand_num, n);

        TH1F hist{"Central Limit", "Central LImit", 100, 0, (double)n};
        for (double x : sums) { hist.Fill(x); }
        TCanvas canv;
        canv.cd();
        hist.Draw();
        std::string name{"sums_" + std::to_string(n) + ".png"};
        canv.SaveAs(name.c_str());

        graph_sigma.SetPoint(n-1, n, variance(sums));
    }

    TCanvas canvas;
    canvas.cd();
    canvas.SetGrid();
    canvas.SetTitle("Central Limit Theorem");
    graph_sigma.GetXaxis()->SetTitle("N");
    graph_sigma.GetYaxis()->SetTitle("Variance");
    graph_sigma.Draw();
    canvas.SaveAs("graph.png");

    return 0;
}
