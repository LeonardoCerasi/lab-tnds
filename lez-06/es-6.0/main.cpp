#include "particle.h"

int main()
{
    particle *p = new particle(1., 2.);
    electron *e = new electron();
    particle *b = new electron();

    p->print();
    e->print();
    b->print();

    delete p;
    delete e;
    delete b;

    return 0;
}
