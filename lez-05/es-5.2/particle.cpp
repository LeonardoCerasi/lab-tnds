#include "particle.h"

// particle class

// constructor

particle::particle (double M, double Q) : m{M}, q{Q} {}

// set methods

void particle::set_mass (double M) { m = M; }

void particle::set_charge (double Q) { q = Q; }

// get methods

double particle::get_mass () const { return m; }

double particle::get_charge () const { return q; }
