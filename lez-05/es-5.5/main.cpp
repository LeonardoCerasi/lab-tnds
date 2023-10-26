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
    
    double delta{10e3};
    double d{2.5e5};
    double r{1e3};
    double m{3e12};

    double phi_goce{std::asin(delta / (r_t + d))};
    double phi_mount{std::asin(r / (r_t + r))};

    std::cout << phi_goce << std::endl << phi_mount << "\n\n\n\n" << std::endl;

    spherical_body earth (m_t, r_t);
    std::vector<spherical_body> mountains;
    position goce (r_t + d, 0., 0.);
    std::vector<vector_field> grav_field;

    try
    {
        for (int i{}; i < 100; i++)
        {
            spherical_body mount(m, r, 's', r_t + r, i * phi_mount, M_PI / 2);
            mountains.push_back(mount);

            std::cout << mount.get_mass() << ", " << mount.get_radius() << std::endl;
            std::cout << mount.get_coordinate('s', 0) << ", " << mount.get_coordinate('s', 1) << ", " << mount.get_coordinate('s', 2) << std::endl;
            std::cout << mount.get_coordinate(0) << ", " << mount.get_coordinate(1) << ", " << mount.get_coordinate(2) << std::endl << std::endl;
        }

        std::cout << "\n\n\n\n" << std::endl;

        for (int i{}; i < std::floor(2 * M_PI / phi_goce); i++)
        {
            goce.set_coordinate('s', 1, i * phi_goce);

            std::cout << i << std::endl;
            std::cout << goce.get_coordinate('s', 0) << ", " << goce.get_coordinate('s', 1) << ", " << goce.get_coordinate('s', 2) << std::endl;
            std::cout << goce.get_coordinate(0) << ", " << goce.get_coordinate(1) << ", " << goce.get_coordinate(2) << std::endl << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
