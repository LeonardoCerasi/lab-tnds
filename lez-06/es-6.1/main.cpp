#include <iostream>

#include "functions.h"

int main()
{
    parabola p (3, 5, -2);

    std::cout << "Vertex: (" << p.vertex() << ", " << p.eval(p.vertex()) << ")" << std::endl;
}
