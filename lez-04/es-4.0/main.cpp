#include <iostream>
#include <vector>
#include <stdexcept>

#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TGraphErrors.h"

#include "func.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Correct use of the code: " << argv[0] << " <input_path> <output_path>." << std::endl;
        
        return -1;
    }

    char *input_path = argv[1];
    char *output_path = argv[2];

    std::vector<std::vector<double>> data;
    try
    {
        data = read_file<double>(input_path);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::vector<Double_t> Delta_V;
    std::vector<Double_t> rB2;
    std::vector<Double_t> rB2_err;

    for (int i = 0; i < (int) data.size(); i++)
    {
        Delta_V.push_back(data[i][0]);
        rB2.push_back(data[i][1]);
        rB2_err.push_back(data[i][2]);
    }

    std::vector<double> lin_reg = linear_regression(Delta_V, rB2, rB2_err);

    std::ofstream output (output_path);
    output << "Linear regression: " << std::endl;
    output << "Slope: " << lin_reg[0] << std::endl;
    output << "Intercept: " << lin_reg[1] << std::endl;
    output << "Slope error: " << lin_reg[2] << std::endl;
    output << "Intercept error: " << lin_reg[3] << std::endl;
    output << "Degree of freedom: " << lin_reg[4] << std::endl;
    output << "Linear correlation: " << lin_reg[5] << std::endl;
    output.close();

    auto canvas = new TCanvas("canvas", "Measurments", 200, 10, 1200, 1200);
    canvas->SetGrid();
    // per qualche motivo non funziona
    // auto graph = new TGraphErrors(Delta_V.size(), &Delta_V, &rB2, nullptr, &rB2_err);

    return 0;
}
