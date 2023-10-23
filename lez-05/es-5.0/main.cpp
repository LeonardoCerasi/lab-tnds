#include <iostream>
#include <stdexcept>

#include "position.h"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage of the programm: " << argv[0] << " <x> <y> <z>" << std::endl;
        return -1;
    }

    position P (atof(argv[1]), atof(argv[2]), atof(argv[3]));
    position O;

    try
    {
        std::cout << "Cartesian coordinates:" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cout << P.get_coordinate(i) << ", ";
        }

        std::cout << "\n\nSpherical coordinates:" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cout << P.get_coordinate('s', i) << ", ";
        }

        std::cout << "\n\nCylindrical coordinates:" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cout << P.get_coordinate('c', i) << ", ";
        }

        std::cout << "\n\nDistance from the origin: " << P.dist(O) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    

    return 0;
}
