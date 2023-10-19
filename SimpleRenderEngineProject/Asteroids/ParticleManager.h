#pragma once

#include <chrono>
#include <ctime>
#include <memory>
#include "Asteroid.h"
#include "Player.h"
#include "LaserShot.h"
#include "utils.h"
#include "Score.h"

class ParticleManager
{
public:
    ParticleManager(int initialAsteroidCount, float spawnInterval);
    void UpdateAsteroids(float deltaTime);
    void RenderAsteroids(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
    void UpdateLasers(float deltaTime);
    void RenderLasers(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder);
    void ShootLaser(std::shared_ptr<Player> player);
    void DetectShotCollisions();
    bool PlayerIsHit(glm::vec2 &playerPos);

private:
    void SpawnAsteroid(int size);
    void RemoveOutOfBoundsAsteroids();
    void RemoveOldLasers();
    std::vector<std::shared_ptr<Asteroid>> ExplodeAsteroid(std::shared_ptr<Asteroid> asteroid);
    std::vector<std::shared_ptr<Asteroid>> asteroids;
    std::vector<std::shared_ptr<LaserShot>> lasers;
    float spawnInterval;
    std::chrono::system_clock::time_point lastSpawnTime;
};
