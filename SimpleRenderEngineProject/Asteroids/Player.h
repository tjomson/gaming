#pragma once

#include <deque>
#include <cstdlib>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "utils.h"

#define TURNINGSPEED 200
#define MOVESPEED 300
#define HEALTHPOINTS 5
#define PLAYERRADIUS 35

enum MovementType
{
    CLOCKWISE,
    COUNTERCLOCKWISE,
    FORWARD,
    BACKWARD,
    NONE
};

class Player
{
public:
    Player(int x, int y);
    void HandleKeyPress(SDL_Event &event);
    void MoveStep(float deltaTime);
    void Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
    void ApplyBound();
    float currHeading = 0;
    MovementType currMovement = NONE;
    glm::vec2 position;
    int hp = HEALTHPOINTS;
};
