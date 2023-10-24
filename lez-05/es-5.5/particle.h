#pragma once

const double e{1.60217646e-19};
const double m_p{1.67262158e-27};
const double m_e{9.10938188e-31};

class particle
{
    protected:

        // intrinsic properties
        double m{};
        double q{};

    public:

        // constructors
        particle () {};
        particle (double, double);

        // set methods
        void set_mass (double);
        void set_charge (double);

        // get methods
        double get_mass () const;
        double get_charge () const;
};
