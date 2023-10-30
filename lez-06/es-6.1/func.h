#pragma once

class function
{
    public:

        virtual double eval (double x) const = 0;

        virtual ~function () {};
};
