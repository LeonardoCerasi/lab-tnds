#pragma once

// includes

#include <iostream>
#include <string>
#include <stdexcept>

// declarations

template <typename Type> class Vector
{
    private:

        int dim;
        
        Type *vector;
    
    public:

        Vector ()
        {
            dim = 0;
            vector = NULL;
        }

        ~Vector () { delete[] vector; }

        Vector (int n);

        Vector (const Vector<Type> &vect);

        Vector<Type> &operator = (const Vector<Type> &vect);

        Vector<Type> &operator = (Vector<Type> &&vect);

        Type &operator [] (int index) const;

        int get_dim () const { return dim; }

        void set_comp (int index, Type comp);

        Type get_comp (int index) const;

        void swap (int index_1, int index_2);
};

// implementations

template <typename Type> Vector<Type>::Vector(int n)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Dimension must be positive, but " + std::to_string(n) + " was given.");
    }
    else
    {
        dim = n;
        vector = new Type[n];

        for (int i = 0; i < n; i++)
        {
            vector[i] = 0;
        }
    }
}

template <typename Type> Vector<Type>::Vector(const Vector<Type> &vect)
{
    dim = vect.dim;
    vector = new Type[dim];

    for (int i = 0; i < dim; i++)
    {
        vector[i] = vect.vector[i];
    }
}

template <typename Type> Vector<Type> &Vector<Type>::operator=(const Vector<Type> &vect)
{
    dim = vect.dim;

    if (vector)
    {
        delete[] vector;
    }
    vector = new double[dim];

    for (int i = 0; i < dim; i++)
    {
        vector[i] = vect.vector[i];
    }

    return *this;
}

template <typename Type> Vector<Type> &Vector<Type>::operator=(Vector<Type> &&vect)
{
    dim = vect.dim;

    if (vector)
    {
        delete[] vector;
    }
    vector = new Type[dim];

    for (int i = 0; i < dim; i++)
    {
        vector[i] = vect.vector[i];
    }

    vect.dim = 0;
    vect.vector = nullptr;

    return *this;
}

template <typename Type> Type &Vector<Type>::operator[](int index) const
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

template <typename Type> void Vector<Type>::set_comp(int index, Type comp)
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

template <typename Type> Type Vector<Type>::get_comp(int index) const
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

template <typename Type> void Vector<Type>::swap(int index_1, int index_2)
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
        Type temp = vector[index_1];

        this->set_comp(index_1, vector[index_2]);
        this->set_comp(index_2, temp);
    }
}
