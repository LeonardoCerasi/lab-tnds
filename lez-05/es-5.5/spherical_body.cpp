#include "spherical_body.h"

// constructors

spherical_body::spherical_body(double M, double R) : m{M}, r{R} {}

spherical_body::spherical_body (double M, double R, double X, double Y, double Z) : m{M}, r{R}, position(X, Y, Z) {}

spherical_body::spherical_body(double M, double R, char type, double X, double Y, double Z) : m{M}, r{R}, position(type, X, Y, Z) {}

spherical_body::spherical_body (double M, double R, const position& P) : m{M}, r{R}, position(P) {}

// set methods

void spherical_body::set_position (const position& P)
{
    x = P.get_coordinate(0);
    y = P.get_coordinate(1);
    z = P.get_coordinate(2);
}

void spherical_body::set_mass (double M) { m = M; }

void spherical_body::set_radius (double R) { r = R; }

// get methods

position spherical_body::get_position () const { return position(x, y, z); }

double spherical_body::get_mass () const { return m; }

double spherical_body::get_radius () const { return r; }

// force fields

vector_field spherical_body::gravitational_field (const position& P) const
{
    vector_field field(P);
    
    if (dist(P) < r)
    {
        field.set_components((g * m * dist(P) / pow(r, 3)), get_position());
    }
    else
    {
        field.set_components((g * m / pow(dist(P), 2)), get_position());
    }

    return field;
}
