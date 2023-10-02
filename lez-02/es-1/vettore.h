#pragma once

#include <iostream>

class Vettore
{
    private:

        int dim;
        double *vect;
    
    public:

        Vettore ()
        {
            dim = 0;
            vect = NULL;
        }

        ~Vettore () { delete[] vect; }

        Vettore(int n);

        int get_dim () const { return dim; }

        void set_comp (int index, double comp);

        double get_comp (int index) const;

        void swap (int index_1, int index_2);
};
