#pragma once

inline double sign (double x)
{
    return (x == 0 ? 0 : (x > 0 ? 1 : -1));
}
