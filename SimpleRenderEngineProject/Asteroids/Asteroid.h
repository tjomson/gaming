#include "sre/SDLRenderer.hpp"
#include "utils.h"

class Asteroid
{
public:
    Asteroid();
    void Update(float deltaTime);
    float angularVelocityFactor;
    float velocityFactor;
    glm::vec2 position;
    int direction;
    bool clockwiseRotation;

private:
    int randInRange(int a, int b);
    glm::vec2 generatePosition();
};
