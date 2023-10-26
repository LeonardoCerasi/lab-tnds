#pragma once

#include <vector>
#include <stdexcept>

#include "position.h"
#include "particle.h"
#include "vector_field.h"

class point_particle : public particle, public position
{
    public:

        // constructors
        point_particle () {}
        point_particle (double, double, double, double, double);
        point_particle (double, double, const position&);

        // get methods
        position get_position () const;

        // force fields
        vector_field electric_field (const position&) const;
        vector_field gravitational_field(const position &) const;
};
