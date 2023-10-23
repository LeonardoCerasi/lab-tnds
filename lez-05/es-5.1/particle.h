#pragma once

class particle
{
    protected:

        // intrinsic properties
        double m;
        double q;

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

// electron class
class electron : public particle
{
public:
    // constructor
    electron();
};
