#include "func.h"

double *ReadDataFromFile(const char *path, int n_data)
{
    std::ifstream input(path);

    if (!input)
    {
        std::cout << "Error while opening file." << std::endl;

        return {};
    }

    double *array = new double[n_data];

    for (int i = 0; i < n_data; i++)
    {
        double temp;
        input >> temp;

        if (input.eof())
        {
            std::cout << "Reached end of file before given data number was reached." << std::endl;

            break;
        }

        array[i] = temp;
    }

    input.close();

    return array;
}

double CalcolaMedia (int n_data, double *data)
{
    double mean = 0;

    for (int i = 0; i < n_data; i++)
    {
        mean += data[i];
    }

    return (mean / double(n_data));
}

double CalcolaVarianza (int n_data, double *data)
{
    double sample_mean = CalcolaMedia(n_data, data);
    double variance = 0;

    for (int i = 0; i < n_data; i++)
    {
        variance += pow(data[i] - sample_mean, 2);
    }

    return (variance / double(n_data));
}

void ScambiaByRef (double &a, double &b)
{
    double temp = b;
    b = a;
    a = temp;
}

void selection_sort (int n_data, double *data)
{
    for (int i = 0; i < n_data - 1; i++)
    {
        for (int j = i + 1; j < n_data; j++)
        {
            if (data[i] > data[j])
            {
                ScambiaByRef(data[i], data[j]);
            }
        }
    }
}

double CalcolaMediana(int n_data, double *data)
{
    if (n_data % 2 == 0)
    {
        return (data[n_data / 2 - 1] + data[n_data / 2]) / 2;
    }
    else
    {
        return data[(n_data - 1) / 2];
    }
}

void Print(const char *path, int n_data, double *data)
{
    std::ofstream output (path);

    output << "Reordered data:\n" << std::endl;
    for (int i = 0; i < n_data; i++)
    {
        output << data[i] << std::endl;
    }

    output.close();
}
