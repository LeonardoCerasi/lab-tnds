#pragma once

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
