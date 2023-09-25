#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

double *ReadDataFromFile (const char *path, int n_data);

double CalcolaMedia (int n_data, double *data);

double CalcolaVarianza(int n_data, double *data);

void ScambiaByRef (double &a, double &b);

void selection_sort (int n_data, double *data);

double CalcolaMediana (int n_data, double *data);

void Print (const char *path, int n_data, double *data);

void Print (int n_data, double *data);
