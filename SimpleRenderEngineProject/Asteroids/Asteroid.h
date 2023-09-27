#pragma once

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "utils.h"

enum AsteroidSize
{
    SMALL = 0,
    MEDIUM = 1,
    BIG = 2
};

class Asteroid
{
public:
    Asteroid(int astSize);
    void Update(float deltaTime);
    void Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
    float angularVelocity;
    float velocity;
    float rotation;
    glm::vec2 position;
    int direction;
    bool clockwiseRotation;
    bool IsOutOfBounds();
    float lifetime;
    int size;

private:
    glm::vec2 generatePosition();
    float randomFraction();
};
