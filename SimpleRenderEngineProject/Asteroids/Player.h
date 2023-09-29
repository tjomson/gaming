#pragma once

#include <deque>
#include <cstdlib>
#include "sre/SpriteAtlas.hpp"
#include "utils.h"
#include <cstdlib>
#include "KeyboardCache.h"

#define TURNINGSPEED 200
#define MOVESPEED 300
#define PLAYERRADIUS 35

class Player
{
public:
    Player(int x, int y);
    void MoveStep(float deltaTime);
    void Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
    bool isDead = false;
    float currHeading = 0;
    glm::vec2 position;

private:
    void ApplyBound();
    std::string GetSpriteName();
};
