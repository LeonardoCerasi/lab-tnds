#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

class Position
{
    private:
        
        double x;
        double y;
        double z;

    public:

        Position() { x = 0; y = 0; z = 0; }
        Position(double x_1, double x_2, double x_3)
        {
            x = x_1;
            y = x_1;
            z = x_3;
        }
        Position(std::vector<double> coord)
        {
            x = coord[0];
            y = coord[1];
            z = coord[2];
        }

        double get_x() { return x; }
        double get_y() { return y; }
        double get_z() { return z; }

        void set_x(double value) { x = value; }
        void set_y(double value) { y = value; }
        void set_z(double value) { z = value; }

        double dist() { return sqrt(x*x + y*y + z*z); }
        double dist(Position p)
        {
            return sqrt(pow(x - p.get_x(), 2) + pow(y - p.get_y(), 2) + pow(z - p.get_z(), 2));
        }

        Position operator= (Position p)
        {
            x = p.get_x();
            y = p.get_y();
            z = p.get_z();

            return *this;
        }

        Position operator+ (Position p) const
        {
            return Position(x + p.get_x(), y + p.get_y(), z + p.get_z());
        }

        Position operator- (Position p) const
        {
            return Position(x - p.get_x(), y - p.get_y(), z - p.get_z());
        }

        Position operator* (double s) const
        {
            return Position(x * s, y * s, z * s);
        }

        Position operator/ (double s) const
        {
            return Position(x / s, y / s, z / s);
        }
};

std::vector<Position> initialize_pos(std::vector<std::vector<double>> coord)
{
    std::vector<Position> pos;

    for (std::vector<double> point : coord)
    {
        pos.push_back(Position(point));
    }

    return pos;
}

void best_path(std::vector<Position> &pos, Position start)
{
    Position ref = start;

    for (std::vector<Position>::iterator it = pos.begin(); it != pos.end(); it++)
    {
        std::sort(it, pos.end(), [&] (Position p_1, Position p_2) { return p_1.dist(ref) < p_2.dist(ref); });
        
        ref = *it;
    }
}
