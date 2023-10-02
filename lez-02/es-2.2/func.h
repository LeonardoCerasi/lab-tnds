#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>

#include "vect.h"

namespace test
{
    bool approximation (double calculated, double expected, double sensibility);

    void test_stat (void);
}

Vector read_file (const char *path, int n_data);

void selection_sort (Vector &vect);

namespace stat
{
    double mean (const Vector &vect);

    double variance (const Vector &vect);

    double median (const Vector &vect);
}

void print (const char *path, const Vector &vect);

void print (const Vector &vect);
