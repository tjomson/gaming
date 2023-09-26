#pragma once

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "utils.h"

class LaserShot
{
public:
    LaserShot(glm::vec2 pos, float head);
    glm::vec2 position;
    float heading;
    float lifetime;
    void Update(float deltaTime);
    void Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
};
