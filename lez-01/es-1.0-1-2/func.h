#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

double *read_file (const char *path, int n_data);

double CalcolaMedia (int n_data, double *data);

double CalcolaVarianza(int n_data, double *data);

void swap (double &a, double &b);

void selection_sort (int n_data, double *data);

double CalcolaMediana (int n_data, double *data);

void Print (const char *path, int n_data, double *data);
