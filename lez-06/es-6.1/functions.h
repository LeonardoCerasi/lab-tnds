#pragma once

#include "func.h"

class parabola : public function
{
    public:

        parabola () {}
        parabola (double A, double B, double C);
        ~parabola () {}

        double eval (double x) const override;

        void set_params (double A, double B, double C);

        double vertex () const;

    protected:

        double a, b, c;
};
