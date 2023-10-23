#pragma once

#include <vector>
#include <stdexcept>

#include "position.h"

class vector_field : public position
{
    protected:

        // components of vector
        double f_x = 0.;
        double f_y = 0.;
        double f_z = 0.;

    public:

        // constructors
        vector_field (double, double, double);
        vector_field (std::vector<double>);
        vector_field (const position&);
        vector_field (double, double, double, double, double, double);
        vector_field(std::vector<double>, double, double, double);
        vector_field (const position&, double, double, double);
        vector_field(double, double, double, std::vector<double>);
        vector_field(std::vector<double>, std::vector<double>);
        vector_field(const position &, std::vector<double>);

        // operator overloading
        vector_field operator+ (const vector_field&) const;
        vector_field operator- (const vector_field &) const;
        vector_field &operator+=(const vector_field &);

        // set methods
        void set_component (int, double);
        void set_position (double, double, double);
        void set_position (const position&);

        // get methods
        double get_component (int) const;
        
        // magnitude
        double mag () const;
};
