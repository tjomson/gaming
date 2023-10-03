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

// AI generated function
float distanceBetweenLineAndPoint(glm::vec2 A, glm::vec2 B, glm::vec2 C)
{
    glm::vec2 AB = B - A;
    glm::vec2 AC = C - A;
    float dotProduct = glm::dot(AB, AC);
    float squaredLengthAB = glm::dot(AB, AB);
    float t = glm::clamp(dotProduct / squaredLengthAB, 0.0f, 1.0f);
    glm::vec2 projection = A + t * AB;
    glm::vec2 distance = projection - C;
    return glm::length(distance);
}
