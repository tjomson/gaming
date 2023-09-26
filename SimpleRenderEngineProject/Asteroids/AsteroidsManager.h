#pragma once

#include "Asteroid.h"

class AsteroidsManager
{
public:
    AsteroidsManager(int initialAsteroidCount);
    void UpdateAsteroids(float deltaTime);
    void SpawnAsteroid();
    void RenderAsteroids(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);

private:
    void RemoveOutOfBoundsAsteroids();
    std::vector<Asteroid *> asteroids;
};
