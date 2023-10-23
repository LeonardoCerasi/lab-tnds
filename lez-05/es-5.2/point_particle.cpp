#include "point_particle.h"

// constructors

point_particle::point_particle (double m, double q, double x, double y, double z) : particle(m, q), position(x, y, z) {}

point_particle::point_particle(double m, double q, std::vector<double> r) : particle(m, q), position(r) {}

point_particle::point_particle(double m, double q, const position& P) : particle(m, q), position(P) {}

// force fields

vector_field point_particle::electric_field (const position& P) const
{
    double E_x = (K * q / pow(dist(P), 2)) * sin(P.get_coordinate('s', 2)) * cos(P.get_coordinate('s', 1));
    double E_y = (K * q / pow(dist(P), 2)) * sin(P.get_coordinate('s', 2)) * sin(P.get_coordinate('s', 1));
    double E_z = (K * q / pow(dist(P), 2)) * cos(P.get_coordinate('s', 2));

    return vector_field(P, E_x, E_y, E_z);
}

vector_field point_particle::gravitational_field(const position &P) const
{
    double G_x = (G * m / pow(dist(P), 2)) * sin(P.get_coordinate('s', 2)) * cos(P.get_coordinate('s', 1));
    double G_y = (G * m / pow(dist(P), 2)) * sin(P.get_coordinate('s', 2)) * sin(P.get_coordinate('s', 1));
    double G_z = (G * m / pow(dist(P), 2)) * cos(P.get_coordinate('s', 2));

    return vector_field(P, G_x, G_y, G_z);
}
