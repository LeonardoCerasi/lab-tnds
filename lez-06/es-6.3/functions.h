#pragma once

#include <cmath>

#include "func.h"

class parabola : public function
{
    protected:

        double a, b, c;

    public:

        parabola () {}
        parabola (double, double, double);
        ~parabola () {}

        double eval (double) const override;

        void set_params (double, double, double);

        double vertex () const;
};

class tangent_eq : public function
{
    public:

        tangent_eq () {}

        double eval (double) const override;
};
