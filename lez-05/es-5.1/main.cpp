#include <iostream>

#include "particle.h"

int main()
{

    particle p (1., 1.6e-19);
    electron *e = new electron();

    std::cout << "Particle: m = " << p.get_mass() << ", q = " << p.get_charge() << std::endl;

    std::cout << "Electron: m = " << e->get_mass() << ", q = " << e->get_charge() << std::endl;

    return 0;
}