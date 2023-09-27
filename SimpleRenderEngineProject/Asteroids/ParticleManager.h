#pragma once

#include <chrono>
#include <ctime>
#include "Asteroid.h"
#include "LaserShot.h"
#include "utils.h"

class ParticleManager
{
public:
    ParticleManager(int initialAsteroidCount, float spawnInterval);
    void UpdateAsteroids(float deltaTime);
    void RenderAsteroids(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
    void UpdateLasers(float deltaTime);
    void RenderLasers(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
    void ShootLaser(glm::vec2 pos, float heading);

private:
    void SpawnAsteroid(int size);
    void RemoveOutOfBoundsAsteroids();
    void RemoveOldLasers();
    std::vector<Asteroid *> asteroids;
    std::vector<LaserShot *> lasers;
    float spawnInterval;
    std::chrono::system_clock::time_point lastSpawnTime;
};
