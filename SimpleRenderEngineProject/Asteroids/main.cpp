#include <iostream>
#include <chrono>
#include <random>
#include <tuple>

#include "Player.h"
#include "Asteroid.h"
#include "ParticleManager.h"
#include "LaserShot.h"
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "Score.h"
#include "KeyboardCache.h"

#pragma region Engine State
#pragma endregion
#pragma region Game State
#pragma endregion
#include "main.h"

Player *player;
ParticleManager *particleManager;

glm::vec2 window_size = glm::vec2(GAMEWIDTH, GAMEHEIGHT);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;
LaserShot *laser;

int main()
{
    std::srand(std::time(nullptr));
    ResetGame();
    renderer.frameRender = Render;
    renderer.frameUpdate = Update;
    renderer.keyEvent = ProcessEvents;
    renderer.setWindowSize(window_size);
    renderer.init();
    camera.setWindowCoordinates();
    atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");
    renderer.startEventLoop();
}

void ResetGame()
{
    Score::score = 0;
    player = new Player(GAMEWIDTH / 2, GAMEHEIGHT / 2);
    particleManager = new ParticleManager(5, 0.5);
}

void ProcessEvents(SDL_Event &event)
{
    KeyboardCache::HandleEvent(event);
}

void Update(float deltaTime)
{
    particleManager->UpdateAsteroids(deltaTime);
    particleManager->UpdateLasers(deltaTime);
    player->MoveStep(deltaTime);
    particleManager->DetectShotCollisions();
    if (particleManager->PlayerIsHit(player->position))
        player->isDead = true;
    if (KeyboardCache::space_clicked)
    {
        KeyboardCache::space_clicked = false;
        if (player->isDead)
            ResetGame();
        else
        {
            particleManager->ShootLaser(player->position, player->currHeading);
        }
    }
}

void Render()
{
    sre::RenderPass renderPass = sre::RenderPass::create()
                                     .withCamera(camera)
                                     .withClearColor(true, {.3f, .3f, 1, 1})
                                     .build();
    sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();
    particleManager->RenderAsteroids(atlas, spriteBatchBuilder);
    particleManager->RenderLasers(atlas, spriteBatchBuilder);

    player->Render(atlas, spriteBatchBuilder);
    Score::Render();
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);
}
