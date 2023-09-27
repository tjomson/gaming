#include "utils.h"

float floatMod(float a, float b)
{
    if (a >= b)
        return a - b;
    if (0 > a)
        return b - a;
    return a;
}

int randInRange(int a, int b)
{
    return a + std::rand() % (b - a + 1);
}
