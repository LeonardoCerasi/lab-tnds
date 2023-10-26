#pragma once

#include <stdexcept>

#include "position.h"

const double k{8.9875517923e9};
const double g{6.67430e-11};

class vector_field : public position
{
    protected:

        // components of vector
        double f_x{};
        double f_y{};
        double f_z{};

    public:

        // constructors
        vector_field () {}
        vector_field (double, double, double);
        vector_field (const position&);
        vector_field (double, double, double, double, double, double);
        vector_field (const position&, double, double, double);

        // operator overloading
        vector_field operator+ (const vector_field&) const;
        vector_field operator- (const vector_field &) const;
        vector_field &operator+= (const vector_field &);

        // set methods
        void set_component (int, double);
        void set_components (double, const position&);

        // get methods
        double get_component (int) const;
        position get_position() const;

        // magnitude
        double mag () const;
};
