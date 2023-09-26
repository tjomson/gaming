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

#pragma region Engine State
#pragma endregion
#pragma region Game State
#pragma endregion
#include "main.h"

auto player = new Player(100, 80);
auto particleManager = new ParticleManager(5, 5);
glm::vec2 window_size = glm::vec2(GAMEWIDTH, GAMEHEIGHT);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;
LaserShot *laser;

int main()
{
    std::srand(std::time(nullptr));
    renderer.frameRender = Render;
    renderer.frameUpdate = Update;
    renderer.keyEvent = ProcessEvents;
    renderer.setWindowSize(window_size);
    renderer.init();
    camera.setWindowCoordinates();
    atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");
    renderer.startEventLoop();
}

void ProcessEvents(SDL_Event &event)
{
    player->HandleKeyPress(event);
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    {
        particleManager->ShootLaser(player->position, player->currHeading);
    }
}

void Update(float deltaTime)
{
    particleManager->UpdateAsteroids(deltaTime);
    particleManager->UpdateLasers(deltaTime);
    player->MoveStep(deltaTime);
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

    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);
}
