#include <iostream>
#include <fstream>

#include "func.h"

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cout << "Use the code as follows: " << argv[0] << "<n_data> <file_path>" << std::endl;

        return -1;
    }

    int n_data = std::atoi(argv[1]);
    char *path = argv[2];

    double *data = ReadDataFromFile(path, n_data);

    std::cout << "\nTheir mean is: " << CalcolaMedia(n_data, data) << std::endl;
    std::cout << "\nTheir variance is: " << CalcolaVarianza(n_data, data) << std::endl;

    selection_sort(n_data, data);

    std::cout << "\nTheir median is: " << CalcolaMediana(n_data, data) << std::endl;

    if (argv[3])
    {
        Print(argv[3], n_data, data);
    }

    return 0;
}
