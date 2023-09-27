#include "ParticleManager.h"

ParticleManager::ParticleManager(int initialAsteroidCount, float interval)
{
    this->spawnInterval = interval;
    lastSpawnTime = std::chrono::system_clock::now();
    for (int i = 0; i < initialAsteroidCount; i++)
    {
        SpawnAsteroid(BIG);
    }
}

void ParticleManager::UpdateAsteroids(float deltaTime)
{
    for (auto asteroid : asteroids)
    {
        asteroid->Update(deltaTime);
    }
    RemoveOutOfBoundsAsteroids();

    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = currentTime - lastSpawnTime;

    if (diff.count() >= spawnInterval)
    {
        lastSpawnTime = currentTime;
        SpawnAsteroid(randInRange(0, 2));
    }
}

void ParticleManager::RenderAsteroids(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder)
{
    for (auto asteroid : asteroids)
    {
        asteroid->Render(atlas, builder);
    }
}

void ParticleManager::RemoveOutOfBoundsAsteroids()
{
    for (auto it = asteroids.begin(); it != asteroids.end();)
    {
        auto currentAsteroid = *it;
        if (currentAsteroid->lifetime > 5 && currentAsteroid->IsOutOfBounds())
        {
            it = asteroids.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void ParticleManager::RemoveOldLasers()
{
    for (auto it = lasers.begin(); it != lasers.end();)
    {
        auto currentLaser = *it;
        if (currentLaser->lifetime > 1)
            it = lasers.erase(it);
        else
            ++it;
    }
    std::cout << lasers.size() << std::endl;
}

void ParticleManager::SpawnAsteroid(int size)
{
    auto asteroid1 = new Asteroid(size);
    asteroids.push_back(asteroid1);
}

void ParticleManager::UpdateLasers(float deltaTime)
{
    for (auto laser : lasers)
    {
        laser->Update(deltaTime);
    }
    RemoveOldLasers();
}

void ParticleManager::RenderLasers(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder)
{
    for (auto laser : lasers)
    {
        laser->Render(atlas, builder);
    }
}

void ParticleManager::ShootLaser(glm::vec2 pos, float heading)
{
    auto laser = new LaserShot(pos, heading);
    lasers.push_back(laser);
}
