#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

class position
{

    protected:

        // cartesian coordinates
        double x{};
        double y{};
        double z{};
    
    public:

        // constructors
        position () {}
        position (double, double, double);
        position(char, double, double, double);

        // operator overloading
        position operator= (const position&);

        // set method
        void set_coordinate (int, double);
        void set_coordinate(char, int, double);
        void set_position (const position& P);

        // get methods
        double get_coordinate (int) const;
        double get_coordinate (char, int) const;

        // distance methods
        double dist (const position&) const;
};
