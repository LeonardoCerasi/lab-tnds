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

    double *data = read_file(path, n_data);

    std::cout << "Read data:" << std::endl;
    for (int i = 0; i < n_data; i++)
    {
        std::cout << data[i] << std::endl;
    }

    std::cout << "\nTheir mean is: " << mean(n_data, data) << std::endl;
    std::cout << "\nTheir variance is: " << variance(n_data, data) << std::endl;

    sel_sort(n_data, data);

    std::cout << "\nTheir median is: " << median(n_data, data) << std::endl;

    if (argv[3])
    {
        write_file(argv[3], n_data, data);
    }

    return 0;
}
