#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

double *read_file (const char *path, int n_data);

double mean (int n_data, double *data);

double variance(int n_data, double *data);

void swap (double &a, double &b);

void sel_sort (int n_data, double *data);

double median (int n_data, double *data);

void write_file (const char *path, int n_data, double *data);
