#pragma once

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "utils.h"

class Asteroid
{
public:
    Asteroid();
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

private:
    int randInRange(int a, int b);
    glm::vec2 generatePosition();
    float randomFraction();
};
