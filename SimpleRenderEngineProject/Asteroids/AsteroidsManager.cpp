#include "AsteroidsManager.h"

AsteroidsManager::AsteroidsManager(int initialAsteroidCount)
{
    for (int i = 0; i < initialAsteroidCount; i++)
    {
        auto asteroid1 = new Asteroid();
        asteroids.push_back(asteroid1);
    }
}

void AsteroidsManager::UpdateAsteroids(float deltaTime)
{
    for (auto asteroid : asteroids)
    {
        asteroid->Update(deltaTime);
    }
    RemoveOutOfBoundsAsteroids();
}

void AsteroidsManager::RenderAsteroids(std::shared_ptr<sre::SpriteAtlas> atlas, sre::SpriteBatch::SpriteBatchBuilder &builder)
{
    for (auto asteroid : asteroids)
    {
        asteroid->Render(atlas, builder);
    }
}

void AsteroidsManager::RemoveOutOfBoundsAsteroids()
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
    std::cout << asteroids.size() << std::endl;
}

void AsteroidsManager::SpawnAsteroid() {}
