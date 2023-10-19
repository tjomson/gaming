#pragma once

#include <memory>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "utils.h"

#define BIGASTEROIDRADIUS 42
#define MEDIUMASTEROIDRADIUS 20
#define SMALLASTEROIDRADIUS 13

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
    Asteroid(std::shared_ptr<Asteroid> toCopy);
    void Update(float deltaTime);
    void Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
    float angularVelocity;
    float velocity;
    float rotation;
    glm::vec2 position;
    float direction;
    bool clockwiseRotation;
    bool IsOutOfBounds();
    float lifetime;
    int size;
    int GetRadius();

private:
    glm::vec2 generatePosition();
    float randomFraction();
};
