#include "Player.h"
#include <cmath>

Player::Player(int x, int y)
{
    position = {x, y};
    isDead = false;
}

std::string Player::GetSpriteName()
{
    if (isDead)
        return "bang.png";
    return "playerShip1_green.png";
}

void Player::Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder)
{
    sre::Sprite playerShip = atlas->get(GetSpriteName());
    playerShip.setPosition(position);
    playerShip.setRotation(currHeading);
    builder.addSprite(playerShip);
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
    if (isDead)
        return;
    auto radians = glm::radians(floatMod(currHeading, 360));
    auto x = (sin(radians) * deltaTime * MOVESPEED) * -1;
    auto y = (cos(radians) * deltaTime * MOVESPEED);

    if (KeyboardCache::w_clicked && !KeyboardCache::s_clicked)
        position += glm::vec2(x, y);
    else if (!KeyboardCache::w_clicked && KeyboardCache::s_clicked)
        position += (glm::vec2(x, y) * glm::vec2(-1, -1));

    if (KeyboardCache::a_clicked && !KeyboardCache::d_clicked)
        currHeading = floatMod((currHeading + deltaTime * TURNINGSPEED), 360.0);
    else if (!KeyboardCache::a_clicked && KeyboardCache::d_clicked)
        currHeading = floatMod((currHeading - deltaTime * TURNINGSPEED), 360.0);

    ApplyBound();
}
