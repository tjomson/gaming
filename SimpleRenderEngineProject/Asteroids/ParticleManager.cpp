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

void ParticleManager::DetectCollisions()
{
    std::vector<Asteroid *> asteroidsToAdd;
    for (auto laserIt = lasers.begin(); laserIt != lasers.end();)
    {
        bool laserRemoved = false;
        auto currLaser = *laserIt;
        for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end();)
        {
            auto currAsteroid = *asteroidIt;
            auto dist = glm::length(currLaser->position - currAsteroid->position);
            if (dist <= currAsteroid->GetRadius())
            {
                laserIt = lasers.erase(laserIt);
                laserRemoved = true;
                // if (currAsteroid->size != SMALL)
                // {
                //     auto newAst = ExplodeAsteroid(currAsteroid);
                //     asteroidsToAdd.insert(asteroidsToAdd.end(), newAst.begin(), newAst.end());
                // }
                // asteroidIt = asteroids.erase(asteroidIt);
            }
            // else
            // {
            ++asteroidIt;
            // }
        }

        if (!laserRemoved)
            ++laserIt;
    }
    asteroids.insert(asteroids.end(), asteroidsToAdd.begin(), asteroidsToAdd.end());
}

std::vector<Asteroid *> ParticleManager::ExplodeAsteroid(Asteroid *asteroid)
{
    auto copy1 = new Asteroid(asteroid);
    copy1->size--;
    copy1->direction = floatMod(copy1->direction + 45, 360);

    auto copy2 = new Asteroid(asteroid);
    copy2->direction = floatMod(copy2->direction - 90, 360);
    asteroids.push_back(copy2);

    std::vector<Asteroid *> newAsteroids = {copy1, copy2};
    return newAsteroids;
}
