#include <iostream>

#include "position.h"
#include "particle.h"
#include "vector_field.h"
#include "point_particle.h"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage of the programm: " << argv[0] << " <x> <y> <z>" << std::endl;
        return -1;
    }

    position P (atof(argv[1]), atof(argv[2]), atof(argv[3]));

    point_particle e (9.1093826e-31, -1.60217653e-19, 0, 0, 0);
    
    try
    {
        vector_field E = e.electric_field(P);

        std::cout << "Electric field at the selected point: " << E.get_component(0) << ", " << E.get_component(1) << ", " << E.get_component(2) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    

    return 0;
}
