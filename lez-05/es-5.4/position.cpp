#include "position.h"

// constructors

position::position (double X, double Y, double Z)
{
    x = X;
    y = Y;
    z = Z;
}

// oprator overloading

position position::operator= (const position& P)
{
    x = P.get_coordinate(0);
    y = P.get_coordinate(1);
    z = P.get_coordinate(2);

    return *this;
}

// set methods

void position::set_coordinate(int n, double value)
{
    switch (n)
    {
        case 0: x = value; break;
        case 1: y = value; break;
        case 2: z = value; break;

        default:
            throw std::invalid_argument("Coordinate number must be 0, 1 or 2, but " + std::to_string(n) + " was given.");
    }
}

// get methods

/**
 * @brief Returns n-th coordinate with respect to O(0,0,0).
 * 
 * @param n Number of coordinate.
 * @return n-th coordinate. 
 */
double position::get_coordinate (int n) const
{
    switch (n)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;

        default:
            throw std::invalid_argument("Coordinate number must be 0, 1 or 2, but " + std::to_string(n) + " was given.");
    }
}

/**
 * @brief Returns n-th coordinate with respect to O(0,0,0).
 * 
 * @param type Type of coordinate system.
 * @param n Number of coordinate.
 * @return n-th coordinate.
 */
double position::get_coordinate (char type, int n) const
{
    switch (type)
    {
        case 's':

            switch (n)
            {
                case 0: return sqrt(x*x + y*y + z*z); // r
                case 1: return atan(y / x); // phi
                case 2: return acos(z / sqrt(x*x + y*y + z*z)); // theta

                default:
                    throw std::invalid_argument("Coordinate number must be 0, 1 or 2, but " + std::to_string(n) + " was given.");
            }
        
        case 'c':

            switch (n)
            {
                case 0: return sqrt(x*x + y*y); // rho
                case 1: return atan(y / x); // phi
                case 2: return acos(z / sqrt(x*x + y*y + z*z)); // theta

                default:
                    throw std::invalid_argument("Coordinate number must be 0, 1 or 2, but " + std::to_string(n) + " was given.");
            }
        
        default:
            throw std::invalid_argument("Coordinate type must be 's' (spherical) or 'c' (cylindrical).");
    }
}

// distance method

double position::dist (const position &P) const
{
    double dist = 0;

    for (int i = 0; i < 3; i++)
    {
        dist += pow(get_coordinate(i) - P.get_coordinate(i), 2);
    }

    return sqrt(dist);
}
