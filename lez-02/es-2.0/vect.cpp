#include "vect.h"

Vector::Vector (int n)
{
    if (n <= 0)
    {
        std::cerr << "Dimension must be positive, but " << n << " was given." << std::endl;
    }
    else
    {
        dim = n;
        vector = new double[n];

        for (int i = 0; i < n; i++) { vector[i] = 0; }
    }
}

void Vector::set_comp (int index, double comp)
{
    if (index >= dim)
    {
        std::cerr << "Index " << index << " out of range " << dim << "." << std::endl;
    }
    else
    {
        vector[index] = comp;
    }
}

double Vector::get_comp (int index) const
{
    if (index >= dim)
    {
        std::cerr << "Index " << index << " out of range " << dim << "." << std::endl;
    }
    else
    {
        return vector[index];
    }
}

void Vector::swap (int index_1, int index_2)
{
    if (index_1 >= dim)
    {
        std::cerr << "Index " << index_1 << " out of range " << dim << "." << std::endl;
    }
    else if (index_2 >= dim)
    {
        std::cerr << "Index " << index_2 << " out of range " << dim << "." << std::endl;
    }
    else
    {
        double temp = vector[index_1];

        this->set_comp(index_1, vector[index_2]);
        this->set_comp(index_2, temp);
    }
}

