#pragma once

#include <vector>
#include <stdexcept>

#include "position.h"
#include "particle.h"
#include "vector_field.h"

const double k = 8.9875517923e9;
const double g = 6.67430e-11;

class point_particle : public particle, public position
{
    public:

        // constructors
        point_particle (double, double, double, double, double);
        point_particle (double, double, std::vector<double>);
        point_particle (double, double, const position&);

        // force fields
        vector_field electric_field (const position&) const;
        vector_field gravitational_field(const position &) const;
};
