#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

class position {

    protected:

        // cartesian coordinates
        double x = 0.;
        double y = 0.;
        double z = 0.;
    
    public:

        // constructors
        position () {}
        position (double, double, double);
        position (std::vector<double>);

        // operator overloading
        position operator= (const position&);

        // set method
        void set_coordinate (int, double);

        // get methods
        double get_coordinate (int) const;
        double get_coordinate(char, int) const;

        // distance methods
        double dist (const position&) const;
};
