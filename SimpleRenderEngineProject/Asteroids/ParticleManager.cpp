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

    if (diff.count() >= spawnInterval * pow(0.97, Score::score))
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
    auto newEnd = std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid *a)
                                 { return a->lifetime > 5 && a->IsOutOfBounds(); });
    asteroids.erase(newEnd, asteroids.end());
}

void ParticleManager::RemoveOldLasers()
{
    auto newEnd = std::remove_if(lasers.begin(), lasers.end(), [](LaserShot *l)
                                 { return l->lifetime > 1; });
    lasers.erase(newEnd, lasers.end());
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

void ParticleManager::ShootLaser(Player *player)
{
    for (int i = 0; i < player->lasersPerShot; i++)
    {
        auto laser = new LaserShot(player->position, player->currHeading + randInRange(player->shotSpread * -1, player->shotSpread));
        lasers.push_back(laser);
    }
}

void ParticleManager::DetectShotCollisions()
{
    std::vector<Asteroid *> asteroidsToAdd;
    for (auto laserIt = lasers.begin(); laserIt != lasers.end();)
    {
        bool laserRemoved = false;
        auto currLaser = *laserIt;
        for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end(); asteroidIt++)
        {
            auto currAsteroid = *asteroidIt;
            auto dist = glm::length(currLaser->position - currAsteroid->position);
            if (distanceBetweenLineAndPoint(currLaser->prevPos, currLaser->position, currAsteroid->position) <= currAsteroid->GetRadius())
            {
                Score::score++;
                laserIt = lasers.erase(laserIt);
                laserRemoved = true;
                if (currAsteroid->size != SMALL)
                {
                    auto newAst = ExplodeAsteroid(currAsteroid);
                    asteroidsToAdd.insert(asteroidsToAdd.end(), newAst.begin(), newAst.end());
                }
                asteroidIt = asteroids.erase(asteroidIt);
                break;
            }
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
    copy1->direction = floatMod(copy1->direction + randInRange(10, 70), 360);

    auto copy2 = new Asteroid(asteroid);
    copy2->size--;
    copy2->direction = floatMod(copy2->direction - randInRange(10, 70), 360);

    std::vector<Asteroid *> newAsteroids = {copy1, copy2};
    return newAsteroids;
}

bool ParticleManager::PlayerIsHit(glm::vec2 &playerPos)
{
    return std::any_of(asteroids.begin(), asteroids.end(), [&playerPos](Asteroid *a)
                       {
        auto dist = glm::length(playerPos - a->position);
        return PLAYERRADIUS + a->GetRadius() >= dist; });
}
