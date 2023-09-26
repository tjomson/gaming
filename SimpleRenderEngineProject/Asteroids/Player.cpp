#include "Player.h"
#include <cmath>

Player::Player(int x, int y)
{
    position = {x, y};
}

void Player::Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder)
{
    sre::Sprite playerShip = atlas->get("playerShip1_green.png");
    playerShip.setPosition(position);
    playerShip.setRotation(currHeading);
    builder.addSprite(playerShip);
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
    if (position.x >= GAMEWIDTH)
        position.x = 0;
    else if (position.x <= 0)
        position.x = GAMEWIDTH - 0;
    if (position.y >= GAMEHEIGHT)
        position.y = 0;
    else if (position.y < 0)
        position.y = GAMEHEIGHT;
}

void Player::MoveStep(float deltaTime)
{
    auto radians = glm::radians(floatMod(currHeading, 360));
    auto x = (sin(radians) * deltaTime * 200) * -1;
    auto y = (cos(radians) * deltaTime * 200);

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