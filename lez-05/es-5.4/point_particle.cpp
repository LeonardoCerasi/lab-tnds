#include "point_particle.h"

// constructors

point_particle::point_particle (double m, double q, double x, double y, double z) : particle(m, q), position(x, y, z) {}

point_particle::point_particle(double m, double q, const position& P) : particle(m, q), position(P) {}

// get methods
position point_particle::get_position () const
{
    return position(x, y, z);
}

// force fields

vector_field point_particle::electric_field (const position& P) const
{
    vector_field field (P);
    field.set_components((k * q / pow(dist(P), 2)), get_position());

    return field;
}

vector_field point_particle::gravitational_field(const position &P) const
{
    vector_field field(P);
    field.set_components((g * m / pow(dist(P), 2)), get_position());

    return field;
}
