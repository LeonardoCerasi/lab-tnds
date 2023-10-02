#include <iostream>
#include <fstream>

#include "func.h"
#include "vect.h"

int main(int argc, char** argv)
{
    test::test_stat();
    
    if (argc < 3)
    {
        std::cout << "Use the code as follows: " << argv[0] << " <n_data> <file_path>" << std::endl;

        return -1;
    }

    int n_data = std::atoi(argv[1]);
    char *path = argv[2];

    Vector vect = read_file(path, n_data);

    std::cout << "Read data:" << std::endl;
    print(vect);

    std::cout << "\nTheir mean is: " << stat::mean(vect) << std::endl;
    std::cout << "\nTheir variance is: " << stat::variance(vect) << std::endl;

    selection_sort(vect);

    std::cout << "\nTheir median is: " << stat::median(vect) << std::endl;

    if (argv[3])
    {
        print(argv[3], vect);
    }

    return 0;
}
