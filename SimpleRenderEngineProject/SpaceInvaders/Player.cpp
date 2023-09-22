#include "Player.h"

Player::Player()
{
    coordinates.clear();
    coordinates.push_front({20, 10});
    frame_skips = 8;
}

void Player::HandleKeyPress(SDL_Event &event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_w:
        if (event.type == SDL_KEYDOWN && currDir != DOWN)
            currDir = UP;
        break;
    case SDLK_s:
        if (event.type == SDL_KEYDOWN && currDir != UP)
            currDir = DOWN;
        break;
    case SDLK_a:
        if (event.type == SDL_KEYDOWN && currDir != RIGHT)
            currDir = LEFT;
        break;
    case SDLK_d:
        if (event.type == SDL_KEYDOWN && currDir != LEFT)
            currDir = RIGHT;
        break;
    }
}

void Player::ApplyBound()
{
    auto front = coordinates.front();
    coordinates.pop_front();
    if (front.x >= GAMEWIDTH)
        front.x = 2;
    else if (front.x <= 1)
        front.x = GAMEWIDTH - 1;
    if (front.y >= GAMEHEIGHT + ROWOFFSET)
        front.y = ROWOFFSET + 1;
    else if (front.y < ROWOFFSET + 1)
        front.y = GAMEHEIGHT + ROWOFFSET - 1;
    coordinates.push_front({front.x, front.y});
}

bool Player::HasLost()
{
    auto front = coordinates.front();
    std::deque<glm::vec2>::iterator it = coordinates.begin();
    if (it != coordinates.end())
        ++it;

    while (it != coordinates.end())
    {
        glm::vec2 coord = *it;
        if (front.x == coord.x && front.y == coord.y)
            return true;
        ++it;
    }
    return false;
}

void Player::MoveStep(float deltaTime)
{
    auto prevFirst = coordinates.front();
    auto stepLength = deltaTime * 150;

    switch (currDir)
    {
    case UP:
        coordinates.push_front({prevFirst.x, prevFirst.y + stepLength});
        break;
    case DOWN:
        coordinates.push_front({prevFirst.x, prevFirst.y - stepLength});
        break;
    case LEFT:
        coordinates.push_front({prevFirst.x - stepLength, prevFirst.y});
        break;
    case RIGHT:
        coordinates.push_front({prevFirst.x + stepLength, prevFirst.y});
        break;
    }
    if (coordinates.front().x != food_pos.x || coordinates.front().y != food_pos.y)
        coordinates.pop_back();
    ApplyBound();
}