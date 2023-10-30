#include "particle.h"

//////////// particle class

// constructor

particle::particle(double M, double Q)
{
    m = M;
    q = Q;
}

// set methods

void particle::set_mass(double M)
{
    m = M;
}

void particle::set_charge(double Q)
{
    q = Q;
}

// get methods

double particle::get_mass() const
{
    return m;
}

double particle::get_charge() const
{
    return q;
}

void particle::print() const
{
    std::cout << "Parent class" << std::endl;
}

//////////// electron class

// constructor

electron::electron() : particle(9.1093826e-31, -1.60217653e-19) {}

void electron::print() const
{
    std::cout << "Derived class" << std::endl;
}
