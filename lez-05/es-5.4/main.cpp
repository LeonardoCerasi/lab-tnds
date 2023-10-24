#include <iostream>
#include <vector>

#include "position.h"
#include "particle.h"
#include "vector_field.h"
#include "point_particle.h"
#include "assert.h"

int main(int argc, char** argv)
{
    test::test_positions();
    test::test_fields();
    
    if (argc != 5)
    {
        std::cerr << "Usage of the programm: " << argv[0] << " <n> <x> <y> <z>" << std::endl;
        return -1;
    }

    int n = atoi(argv[1]);
    position P(atof(argv[2]), atof(argv[3]), atof(argv[4]));

    double d = 1e-10;
    std::vector<point_particle> charges;
    for (int i = 1; i <= n; i++)
    {
        charges.push_back(point_particle(1, pow(-1,i)*e, d*cos(2*M_PI*(i/n)), d*sin(2*M_PI*i/n), 0.));
    }

    try
    {
        vector_field E (P);
        for (int i = 0; i < n; i++)
        {
            E += charges[i].electric_field(P);
        }

        std::cout << "Electric field at the selected point: " << E.get_component(0) << ", " << E.get_component(1) << ", " << E.get_component(2) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
