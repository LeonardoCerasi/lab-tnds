#pragma once

#include <iostream>

#include "func.h"

class roots
{
    protected:

        double a, b;
        double precision = 1e-3;
        int n_max = 100;

    public:

        roots () {}
        roots(double epsilon) { precision = epsilon; }
        roots(double epsilon, int max_iter)
        {
            precision = epsilon;
            n_max = max_iter;
        }
        virtual ~roots() { std::cout << "destructor" << std::endl; }

        virtual double find_roots (double, double, const function &) = 0;

        void set_precision(double epsilon) { precision = epsilon; }
        void set_max_iter(int max_iter) { n_max = max_iter; }

        double get_precision() const { return precision; }
        int get_max_iter () const { return n_max; }
};
