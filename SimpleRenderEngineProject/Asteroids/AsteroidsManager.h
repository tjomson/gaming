#pragma once

#include <chrono>
#include <ctime>
#include "Asteroid.h"

class AsteroidsManager
{
public:
    AsteroidsManager(int initialAsteroidCount, float spawnInterval);
    void UpdateAsteroids(float deltaTime);
    void SpawnAsteroid();
    void RenderAsteroids(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);

private:
    void RemoveOutOfBoundsAsteroids();
    std::vector<Asteroid *> asteroids;
    float spawnInterval;
    std::chrono::system_clock::time_point lastSpawnTime;
};
