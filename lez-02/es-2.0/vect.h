#pragma once

#include <iostream>

class Vector
{
    private:

        int dim;

        double *vector;
    
    public:

        Vector ()
        {
            dim = 0;
            vector = NULL;
        }

        ~Vector () { delete[] vector; }

        Vector (int n);

        int get_dim () const { return dim; }

        void set_comp (int index, double comp);

        double get_comp (int index) const;

        void swap (int index_1, int index_2);
};
