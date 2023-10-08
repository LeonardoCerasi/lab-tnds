#include "vect.h"

Vector::Vector (int n)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Dimension must be positive, but " + std::to_string(n) + " was given.");
    }
    else
    {
        dim = n;
        vector = new double[n];

        for (int i = 0; i < n; i++) { vector[i] = 0; }
    }
}

Vector::Vector(const Vector &vect)
{
    dim = vect.dim;
    vector = new double[dim];

    for (int i = 0; i < dim; i++) { vector[i] = vect.vector[i]; }
}

Vector &Vector::operator = (const Vector &vect)
{
    dim = vect.dim;

    if (vector) { delete[] vector; }
    vector = new double[dim];

    for (int i = 0; i < dim; i++) { vector[i] = vect.vector[i]; }

    return *this;
}

Vector &Vector::operator = (Vector &&vect)
{
    dim = vect.dim;

    if (vector) { delete[] vector; }
    vector = new double[dim];

    for (int i = 0; i < dim; i++) { vector[i] = vect.vector[i]; }

    vect.dim = 0;
    vect.vector = nullptr;

    return *this;
}

double &Vector::operator [] (int index) const
{
    if (index >= dim)
    {
        throw std::invalid_argument("Index " + std::to_string(index) + " out of range " + std::to_string(dim) + ".");
    }
    else
    {
        return vector[index];
    }
}

void Vector::set_comp (int index, double comp)
{
    if (index >= dim)
    {
        throw std::invalid_argument("Index " + std::to_string(index) + " out of range " + std::to_string(dim) + ".");
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
        throw std::invalid_argument("Index " + std::to_string(index) + " out of range " + std::to_string(dim) + ".");
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
        throw std::invalid_argument("Index " + std::to_string(index_1) + " out of range " + std::to_string(dim) + ".");
    }
    else if (index_2 >= dim)
    {
        throw std::invalid_argument("Index " + std::to_string(index_2) + " out of range " + std::to_string(dim) + ".");
    }
    else
    {
        double temp = vector[index_1];

        this->set_comp(index_1, vector[index_2]);
        this->set_comp(index_2, temp);
    }
}
