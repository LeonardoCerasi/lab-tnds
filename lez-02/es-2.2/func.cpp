#include "func.h"

bool test::approximation(double calculated, double expected, double sensibility = 1e-7)
{
    return (fabs(calculated - expected) < sensibility);
}

void test::test_stat (void)
{
    Vector vect (4);
    for (int i = 0; i < vect.get_dim(); i++) { vect[i] = i + 1; }

    assert (test::approximation(stat::mean(vect), 2.5));
    assert (test::approximation(stat::variance(vect), 1.25));
    assert (test::approximation(stat::median(vect), 2.5));
}

Vector read_file(const char *path, int n_data)
{
    std::ifstream input(path);

    if (!input)
    {
        std::cerr << "Error while opening file." << std::endl;
    }

    Vector vect (n_data);

    for (int i = 0; i < n_data; i++)
    {
        double temp;
        input >> temp;

        if (input.eof())
        {
            std::cerr << "Reached end of file at line " << i << " before given data number " << n_data << " was reached." << std::endl;

            break;
        }

        vect[i] = temp;
    }

    input.close();

    return vect;
}

void selection_sort (Vector &vect)
{
    for (int i = 0; i < vect.get_dim() - 1; i++)
    {
        for (int j = i + 1; j < vect.get_dim(); j++)
        {
            if (vect[i] > vect[j])
            {
                vect.swap(i, j);
            }
        }
    }
}

double stat::mean (const Vector &vect)
{
    double mean = 0;

    for (int i = 0; i < vect.get_dim(); i++)
    {
        mean += vect[i];
    }

    return (mean / double(vect.get_dim()));
}

double stat::variance (const Vector &vect)
{
    double mean = stat::mean(vect);
    double variance = 0;

    for (int i = 0; i < vect.get_dim(); i++)
    {
        variance += pow(vect[i] - mean, 2);
    }

    return (variance / double(vect.get_dim()));
}

double stat::median(const Vector &vect)
{
    if (vect.get_dim() % 2 == 0)
    {
        return (vect[vect.get_dim() / 2 - 1] + vect[vect.get_dim() / 2]) / 2;
    }
    else
    {
        return vect[vect.get_dim() / 2 - 1];
    }
}

void print(const char *path, const Vector &vect)
{
    std::ofstream output (path);

    output << "Reordered data:\n" << std::endl;
    for (int i = 0; i < vect.get_dim(); i++)
    {
        output << vect[i] << std::endl;
    }

    output.close();
}

void print(const Vector &vect)
{
    for (int i = 0; i < vect.get_dim(); i++)
    {
        std::cout << vect[i] << std::endl;
    }
}
