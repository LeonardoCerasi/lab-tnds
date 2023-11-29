#include <iostream>
#include "TH1F.h"
#include "TCanvas.h"

#include "random_gen.h"
#include "assert.h"

int main()
{
    test::test_random();

    random_gen rand_gen{1};
    
    // uniform distribution
    std::vector<double> rand_unif;
    for (int i{}; i < 10000; i++) { rand_unif.push_back(rand_gen.unif(5, 10)); }

    TH1F hist_unif{"Uniform", "Uniform Distribution", 100, 4, 11};
    for (double x : rand_unif) { hist_unif.Fill(x); }

    TCanvas canvas_unif;
    canvas_unif.cd();
    hist_unif.Draw();
    canvas_unif.SaveAs("hist_unif.png");

    // exponential distribution
    std::vector<double> rand_exp;
    for (int i{}; i < 10000; i++) { rand_exp.push_back(rand_gen.exp(1)); }

    TH1F hist_exp{"Exponential", "Exponential Distribution", 100, 0, 10};
    for (double x : rand_exp) { hist_exp.Fill(x); }

    TCanvas canvas_exp;
    canvas_exp.cd();
    hist_exp.Draw();
    canvas_exp.SaveAs("hist_exp.png");

    // gaussian distribution (box-muller)
    std::vector<double> rand_bm;
    for (int i{}; i < 10000; i++) { rand_bm.push_back(rand_gen.gauss_bm(2, 1)); }

    TH1F hist_bm{"Box-MUller", "Box-Muller Distribution", 100, -2, 6};
    for (double x : rand_bm) { hist_bm.Fill(x); }

    TCanvas canvas_bm;
    canvas_bm.cd();
    hist_bm.Draw();
    canvas_bm.SaveAs("hist_bm.png");

    // gaussian distribution accept-reject
    std::vector<double> rand_ar;
    for (int i{}; i < 10000; i++) { rand_ar.push_back(rand_gen.gauss_ar(2, 1)); }

    TH1F hist_ar{"Accept-Reject", "Accept-Reject Distribution", 100, -2, 6};
    for (double x : rand_ar) { hist_ar.Fill(x); }

    TCanvas canvas_ar;
    canvas_ar.cd();
    hist_ar.Draw();
    canvas_ar.SaveAs("hist_ar.png");
    
    return 0;
}
