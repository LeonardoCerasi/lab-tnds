#include <iostream>
#include <fstream>
#include <vector>

#include "func.h"

int main(int argc, char **argv)
{
    test::test_stat();

    if (argc < 3)
    {
        std::cout << "Use the code as follows: " << argv[0] << " <n_data> <input_path> <output_path>" << std::endl;

        return -1;
    }

    int n_data = std::atoi(argv[1]);
    char *path = argv[2];

    std::vector<double> vect = read_file<double>(path, n_data);

    std::cout << "Read data:" << std::endl;
    print<double>(vect);

    std::cout << "\nTheir mean is: " << stat::mean<double>(vect) << std::endl;
    std::cout << "\nTheir variance is: " << stat::variance<double>(vect) << std::endl;
    std::cout << "\nTheir median is: " << stat::median<double>(vect) << std::endl;

    if (argv[3])
    {
        print<double>(argv[3], vect);
    }

    return 0;
}
