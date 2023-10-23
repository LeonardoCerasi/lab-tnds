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

    position P(atof(argv[1]), atof(argv[2]), atof(argv[3]));

    double d = 1e-10;
    point_particle proton (m_p, e, 0, 0, d/2);
    point_particle electron (m_e, -e, 0, 0, -d/2);

    try
    {
        vector_field E = proton.electric_field(P) + electron.electric_field(P);

        std::cout << "Electric field at the selected point: " << E.get_component(0) << ", " << E.get_component(1) << ", " << E.get_component(2) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
