#include "Player.h"
#include <cmath>

Player::Player()
{
}

float floatMod(float a, float b)
{
    if (a >= b)
        return a - b;
    return a;
}

void Player::HandleKeyPress(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            currMovement = FORWARD;
            break;
        case SDLK_s:
            currMovement = BACKWARD;
            break;
        case SDLK_a:
            currMovement = COUNTERCLOCKWISE;
            break;
        case SDLK_d:
            currMovement = CLOCKWISE;
            break;
        default:
            currMovement = NONE;
        }
    }
    else
    {
        currMovement = NONE;
    }
}

void Player::ApplyBound()
{
    // auto front = coordinates.front();
    // coordinates.pop_front();
    // if (front.x >= GAMEWIDTH)
    //     front.x = 2;
    // else if (front.x <= 1)
    //     front.x = GAMEWIDTH - 1;
    // if (front.y >= GAMEHEIGHT + ROWOFFSET)
    //     front.y = ROWOFFSET + 1;
    // else if (front.y < ROWOFFSET + 1)
    //     front.y = GAMEHEIGHT + ROWOFFSET - 1;
    // coordinates.push_front({front.x, front.y});
}

void Player::MoveStep(float deltaTime)
{
    auto x = (sin(glm::radians(floatMod(currHeading, 360))) * 10) * -1;
    auto y = (cos(glm::radians(floatMod(currHeading, 360))) * 10);
    std::cout << x << " " << y << std::endl;

    switch (currMovement)
    {
    case CLOCKWISE:
        currHeading = floatMod((currHeading - deltaTime * 100), 360.0);
        break;
    case COUNTERCLOCKWISE:
        currHeading = floatMod((currHeading + deltaTime * 100), 360.0);
        break;
    case FORWARD:
        position += glm::vec2(x, y);
        break;
    case BACKWARD:
        position += (glm::vec2(x, y) * glm::vec2(-1, -1));
        break;
    case NONE:
        break;
    }
    ApplyBound();
}