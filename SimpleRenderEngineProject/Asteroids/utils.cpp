#include "utils.h"

float floatMod(float a, float b)
{
    if (a >= b)
        return a - b;
    if (0 > a)
        return b - a;
    return a;
}
