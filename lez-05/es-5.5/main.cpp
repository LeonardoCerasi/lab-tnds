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

    spherical_body earth (m_t, r_t);
    std::vector<spherical_body> mountains;
    position goce (r_t + d, 0., 0.);
    std::vector<double> grav_field;

    double earth_field = earth.gravitational_field(goce).mag();
    std::cout << "The ideal Earth's gravitational field at GOCE orbit is " << earth_field << " N/kg." << std::endl;

    try
    {
        for (int i{}; i < 100; i++)
        {
            spherical_body mount(m, r, 's', r_t + r, i * phi_mount, M_PI / 2);
            mountains.push_back(mount);
        }

        for (int i{}; i < std::floor(2 * M_PI / phi_goce); i++)
        {
            goce.set_coordinate('s', 1, i * phi_goce);
            
            vector_field G (goce);
            for (spherical_body mount : mountains)
            {
                G += mount.gravitational_field(goce);
            }

            grav_field.push_back(G.mag() / earth_field);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
