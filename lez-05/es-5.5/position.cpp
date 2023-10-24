#include "position.h"

// constructors

position::position (double X, double Y, double Z) : x{X}, y{Y}, z{Z} {}

position::position (char type, double X, double Y, double Z)
{
    switch (type)
    {
        case 's': // X = r, Y = phi, Z = theta
            x = X * cos(Y) * sin(Z);
            y = X * sin(Y) * sin(Z);
            z = X * cos(Z);
            break;

        case 'c': // X = rho, Y = phi, Z = z
            x = X * cos(Y);
            y = X * sin(Y);
            z = Z;
            break;
        
        default:
            throw std::invalid_argument("Coordinate type must be 's' (spherical) or 'c' (cylindrical).");
    }
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

void position::set_coordinate(char type, int n, double value)
{
    switch (type)
    {
        case 's':

            switch (n)
            {
                case 0: // r
                    set_coordinate(0, value * cos(get_coordinate('s', 1)) * sin(get_coordinate('s', 2)));
                    set_coordinate(1, value * sin(get_coordinate('s', 1)) * sin(get_coordinate('s', 2)));
                    set_coordinate(2, value * cos(get_coordinate('s', 2)));
                    break;
                case 1: // phi
                    set_coordinate(0, get_coordinate('s', 0) * cos(value) * sin(get_coordinate('s', 2)));
                    set_coordinate(1, get_coordinate('s', 0) * sin(value) * sin(get_coordinate('s', 2)));
                    break;
                case 2: // theta
                    set_coordinate(0, get_coordinate('s', 0) * cos(get_coordinate('s', 1)) * sin(value));
                    set_coordinate(1, get_coordinate('s', 0) * sin(get_coordinate('s', 1)) * sin(value));
                    set_coordinate(2, get_coordinate('s', 0) * cos(value));
                    break;

                default:
                    throw std::invalid_argument("Coordinate number must be 0, 1 or 2, but " + std::to_string(n) + " was given.");
            }
            break;
        
        case 'c':

            switch (n)
            {
                case 0: // rho
                    set_coordinate(0, value * cos(get_coordinate('c', 1)));
                    set_coordinate(1, value * sin(get_coordinate('c', 1)));
                    break;
                case 1: // phi
                    set_coordinate(0, get_coordinate('c', 0) * cos(value));
                    set_coordinate(1, get_coordinate('c', 0) * sin(value));
                    break;
                case 2: // z
                    set_coordinate(2, value);
                    break;

                default:
                    throw std::invalid_argument("Coordinate number must be 0, 1 or 2, but " + std::to_string(n) + " was given.");
            }
            break;
        
        default:
            throw std::invalid_argument("Coordinate type must be 's' (spherical) or 'c' (cylindrical).");
    }
}

void position::set_position(const position &P)
{
    x = P.get_coordinate(0);
    y = P.get_coordinate(1);
    z = P.get_coordinate(2);
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
                case 2: return acos(z / sqrt(x*x + y*y + z*z)); // z

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
    return sqrt(pow(get_coordinate(0) - P.get_coordinate(0), 2) +
                pow(get_coordinate(1) - P.get_coordinate(1), 2) +
                pow(get_coordinate(2) - P.get_coordinate(2), 2));
}
