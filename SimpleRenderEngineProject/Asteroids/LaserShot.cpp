#include "LaserShot.h"

LaserShot::LaserShot(glm::vec2 pos, float head)
{
    position = pos;
    heading = head;
    lifetime = 0;
}

void LaserShot::Update(float deltaTime)
{
    lifetime += deltaTime;

    auto radians = glm::radians(floatMod(heading, 360));
    auto x = (sin(radians) * deltaTime * 1000) * -1;
    auto y = (cos(radians) * deltaTime * 1000);
    position += glm::vec2(x, y);
}

void LaserShot::Render(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder)
{
    sre::Sprite laser = atlas->get("laserRed16.png");
    laser.setPosition(position);
    laser.setRotation(heading);
    builder.addSprite(laser);
}
