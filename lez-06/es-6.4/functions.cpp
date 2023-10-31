#include "functions.h"

parabola::parabola (double A, double B, double C)
{
    a = A;
    b = B;
    c = C;
}

double parabola::eval (double x) const
{
    return (a * x * x + b * x + c);
}

void parabola::set_params (double A, double B, double C)
{
    a = A;
    b = B;
    c = C;
}

double parabola::vertex () const
{
    return (-b / (2 * a));
}
