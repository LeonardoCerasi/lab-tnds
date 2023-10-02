#include "vettore.h"

Vettore::Vettore(int n)
{
    if (n <= 0)
    {
        std::cerr << "Dimension must be positive" << std::endl;
    }
    else
    {
        this->dim = n;
        this->vect = new double[n];

        for (int i = 0; i < n; i++) { vect[i] = 0; }
    }
}

void Vettore::set_comp(int index, double comp)
{
    this->vect[index] = comp;
}

double Vettore::get_comp(int index) const
{
    return this->vect[index];
}

void Vettore::swap (int index_1, int index_2)
{
    double temp = this->vect[index_1];

    this->set_comp(index_1, this->vect[index_2]);
    this->set_comp(index_2, temp);
}
