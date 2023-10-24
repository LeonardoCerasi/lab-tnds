#include "vector_field.h"

// constructors

vector_field::vector_field (double x, double y, double z) : position(x, y, z) {}

vector_field::vector_field (const position& P) : position(P) {}

vector_field::vector_field (double x, double y, double z, double fx, double fy, double fz) : position(x, y, z)
{
    f_x = fx;
    f_y = fy;
    f_z = fz;
}

vector_field::vector_field (const position& P, double fx, double fy, double fz) : position(P)
{
    f_x = fx;
    f_y = fy;
    f_z = fz;
}

// operator overloading

vector_field vector_field::operator+ (const vector_field& f) const
{
    if ((f.get_coordinate(0) != x) || (f.get_coordinate(1) != y) || (f.get_coordinate(2) != z))
    {
        throw std::invalid_argument("Sum of vector fields can only be made in the same points.");
    }

    return vector_field(x, y, z, f_x + f.get_component(0), f_y + f.get_component(1), f_x + f.get_component(2));
}

vector_field vector_field::operator- (const vector_field& f) const
{
    if ((f.get_coordinate(0) != x) || (f.get_coordinate(1) != y) || (f.get_coordinate(2) != z))
    {
        throw std::invalid_argument("Sum of vector fields can only be made in the same points.");
    }

    return vector_field(x, y, z, f_x - f.get_component(0), f_y - f.get_component(1), f_x - f.get_component(2));
}

vector_field& vector_field::operator+= (const vector_field& f)
{
    return (*this = (*this + f));
}

// set methods

/**
 * @brief Set n-th component to a value with respect to O(0,0,0).
 * 
 * @param n Numberof coordinate.
 * @param value Value with respect to O(0,0,0).
 */
void vector_field::set_component (int n, double value)
{
    switch (n)
    {
        case 0: f_x = value; break;
        case 1: f_y = value; break;
        case 2: f_z = value; break;

        default:
            throw std::invalid_argument("Component number must be 0, 1 or 2, but " + std::to_string(n) + " was given.");
    }
}

/**
 * @brief Set components calculated by its magnitude and direction.
 * 
 * @param magnitude Magnitude of vector.
 * @param P Source point which gives the direction of vector with respect to its position.
 */
void vector_field::set_components (double magnitude, const position& P)
{
    double u_x = (x - P.get_coordinate(0)) / dist(P);
    double u_y = (y - P.get_coordinate(1)) / dist(P);
    double u_z = (z - P.get_coordinate(2)) / dist(P);

    f_x = magnitude * u_x;
    f_y = magnitude * u_y;
    f_z = magnitude * u_z;
}

void vector_field::set_position (double X, double Y, double Z)
{
    x = X;
    y = Y;
    z = Z;
}

void vector_field::set_position (const position& P)
{
    x = P.get_coordinate(0);
    y = P.get_coordinate(1);
    z = P.get_coordinate(2);
}

// get methods

double vector_field::get_component (int n) const
{
    switch (n)
    {
        case 0: return f_x;
        case 1: return f_y;
        case 2: return f_z;

        default:
            throw std::invalid_argument("Component number must be 0, 1 or 2, but " + std::to_string(n) + " was given.");
    }
}

position vector_field::get_position() const
{
    return position(x, y, z);
}

// magnitude

double vector_field::mag () const
{
    return sqrt(f_x*f_x + f_y*f_y + f_z*f_z);
}
