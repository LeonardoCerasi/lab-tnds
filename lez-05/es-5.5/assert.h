#include <cassert>
#include <cmath>

#include "position.h"
#include "particle.h"
#include "vector_field.h"
#include "point_particle.h"


#include <iostream>
namespace test
{
    bool are_close (double calculated, double expected, double epsilon = 1e-7)
    {
        return (fabs(calculated - expected) < epsilon);
    }

    void test_positions (void)
    {
        position P (1., 2., 3.);

        assert(are_close(P.get_coordinate(0), 1.0));
        assert(are_close(P.get_coordinate(1), 2.0));
        assert(are_close(P.get_coordinate(2), 3.0));

        assert(are_close(P.get_coordinate('s', 0), 3.7416573867739));
        assert(are_close(P.get_coordinate('s', 1), 1.1071487177941));
        assert(are_close(P.get_coordinate('s', 2), 0.64052231267943));

        assert(are_close(P.get_coordinate('c', 0), 2.2360679774998));
        assert(are_close(P.get_coordinate('c', 1), 1.1071487177941));
        assert(are_close(P.get_coordinate('c', 2), 0.64052231267943));
    }

    void test_fields (void)
    {
        position P (-2., 4., 1.);

        // Coulomb's law
        point_particle p1 (0., 5e-7, 5., 3., -2.);
        vector_field E = p1.electric_field(P);

        assert(are_close(E.get_component(0), -69.41150052142065));
        assert(are_close(E.get_component(1), 9.915928645917235));
        assert(are_close(E.get_component(2), 29.747785937751708));

        // Newton's law
        point_particle p2 (1e12, 0., 5., 3., -2.);
        vector_field G = p2.gravitational_field(P);

        //assert(are_close(G.get_component(0), -1.0302576701177));
        //assert(are_close(G.get_component(1), 0.14717966715968));
        //assert(are_close(G.get_component(2), 0.44153900147903));

        assert(are_close(G.get_component(0), -1.030921854));
        assert(are_close(G.get_component(1), 0.1472745506));
        assert(are_close(G.get_component(2), 0.4418236518));
    }
}