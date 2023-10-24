#include <iostream>
#include <vector>
#include <cmath>

#include "position.h"
#include "particle.h"
#include "vector_field.h"
#include "point_particle.h"
#include "spherical_body.h"
#include "assert.h"

int main(int argc, char** argv)
{
    test::test_positions();
    test::test_fields();
    
    double d{2.5e5};
    double r{1e3};
    double m{3e12};

    spherical_body earth (m_t, r_t);
    std::vector<spherical_body> mountains;

    try
    {
        for (int i{}; i < 100; i++)
        {
            spherical_body mount(m, r, 's', r_t + r, i * asin(r / r_t), M_PI / 2);
            mountains.push_back(mount);

            std::cout << mount.get_mass() << ", " << mount.get_radius() << std::endl;
            std::cout << mount.get_coordinate('s', 0) << ", " << mount.get_coordinate('s', 1) << ", " << mount.get_coordinate('s', 2) << std::endl;
            std::cout << mount.get_coordinate(0) << ", " << mount.get_coordinate(1) << ", " << mount.get_coordinate(2) << std::endl << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
