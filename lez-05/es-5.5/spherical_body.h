#pragma once

#include "position.h"
#include "vector_field.h"

const double m_t{5.9722e24};
const double r_t{6.371e6};
const double m_s{1.9885e30};
const double r_s{6.957e8};

class spherical_body : public position
{
    protected:

        // intrinsic properties
        double m{};
        double r{};

    public:

        // constructors
        spherical_body () {}
        spherical_body (double, double);
        spherical_body (double, double, double, double, double);
        spherical_body (double, double, char,  double, double, double);
        spherical_body (double, double, const position&);

        // set methods
        void set_position (const position&);
        void set_mass (double);
        void set_radius (double);

        // get methods
        position get_position () const;
        double get_mass () const;
        double get_radius () const;

        // force field
        vector_field gravitational_field(const position&) const;
};
