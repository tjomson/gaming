#include "Asteroid.h"

Asteroid::Asteroid()
{
    velocity = randomFraction() * 200;
    angularVelocity = randomFraction() * 2;
    clockwiseRotation = randomFraction() < 0.5;
    direction = randomFraction() * 360;
    position = generatePosition();
    rotation = 0;
}

void Asteroid::Update(float deltaTime)
{
    auto radians = glm::radians(floatMod(direction, 360));
    auto x = (sin(radians) * deltaTime);
    auto y = (cos(radians) * deltaTime);
    position += glm::vec2(x, y) * velocity;
    rotation += clockwiseRotation ? angularVelocity : angularVelocity * -1;
}

int Asteroid::randInRange(int a, int b)
{
    return a + std::rand() % (b - a + 1);
}

float Asteroid::randomFraction()
{
    return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

glm::vec2 Asteroid::generatePosition()
{
    int x;
    int y;

    if (direction < 90)
    {
        x = randInRange(-(GAMEWIDTH / 2), GAMEWIDTH / 2);
        if (x > 0)
            y = -50;
        else
            y = randInRange(0, GAMEHEIGHT / 2);
    }
    else if (direction < 180)
    {
        x = randInRange(-(GAMEWIDTH / 2), GAMEWIDTH / 2);
        if (x > 0)
            y = GAMEWIDTH + 50;
        else
            y = randInRange(GAMEHEIGHT / 2, GAMEHEIGHT * 1.5);
    }
    else if (direction < 270)
    {
        x = randInRange((GAMEWIDTH / 2), GAMEWIDTH * 1.5);
        if (x < GAMEWIDTH)
            y = GAMEWIDTH + 50;
        else
            y = randInRange(GAMEHEIGHT / 2, GAMEHEIGHT * 1.5);
    }
    else
    {
        x = randInRange((GAMEWIDTH / 2), -(GAMEWIDTH / 2));
        if (x < GAMEWIDTH)
            y = -50;
        else
            y = randInRange(0, GAMEHEIGHT / 2);
    }

    return glm::vec2(x, y);
}