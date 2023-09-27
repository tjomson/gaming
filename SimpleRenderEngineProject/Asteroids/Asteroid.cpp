#include "Asteroid.h"
#include <string>

Asteroid::Asteroid(int astSize)
{
    velocity = randomFraction() * 200;
    angularVelocity = randomFraction() * 2;
    clockwiseRotation = randomFraction() < 0.5;
    direction = randomFraction() * 360;
    position = generatePosition();
    rotation = 0;
    lifetime = 0;
    size = astSize;
}

Asteroid::Asteroid(Asteroid *toCopy)
{
    velocity = toCopy->velocity;
    angularVelocity = toCopy->angularVelocity;
    clockwiseRotation = toCopy->clockwiseRotation;
    direction = toCopy->direction;
    position = toCopy->position;
    rotation = toCopy->rotation;
    lifetime = toCopy->lifetime;
    size = toCopy->size;
}

int Asteroid::GetRadius()
{
    switch (size)
    {
    case 0:
        return 13;
    case 1:
        return 20;
    case 2:
        return 42;
    }
}

bool Asteroid::IsOutOfBounds()
{
    return position.x > GAMEWIDTH + 100 || position.x < -100 || position.y > GAMEHEIGHT + 100 || position.y < -100;
}

void Asteroid::Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder)
{
    std::string fileName;
    switch (size)
    {
    case BIG:
        fileName = "meteorGrey_big4.png";
        break;
    case MEDIUM:
        fileName = "meteorGrey_med2.png";
        break;
    case SMALL:
        fileName = "meteorGrey_small2.png";
        break;
    }
    sre::Sprite astSprite = atlas->get(fileName);
    astSprite.setPosition(position);
    astSprite.setRotation(rotation);
    builder.addSprite(astSprite);
}

void Asteroid::Update(float deltaTime)
{
    auto radians = glm::radians(floatMod(direction, 360));
    auto x = (sin(radians) * deltaTime);
    auto y = (cos(radians) * deltaTime);
    position += glm::vec2(x, y) * velocity;
    rotation += clockwiseRotation ? angularVelocity : angularVelocity * -1;
    lifetime += deltaTime;
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
