#include <iostream>
#include <chrono>
#include <random>
#include <tuple>

#include "Player.h"
#include "Asteroid.h"
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#pragma region Engine State
#pragma endregion
#pragma region Game State
#pragma endregion
#include "main.h"

auto player = new Player(100, 80);
std::vector<Asteroid *> asteroids;
glm::vec2 window_size = glm::vec2(GAMEWIDTH, GAMEHEIGHT);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

int main()
{
    for (int i = 0; i < 5; i++)
    {
        auto asteroid1 = new Asteroid();
        asteroids.push_back(asteroid1);
    }

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
}

void Update(float deltaTime)
{
    for (auto asteroid : asteroids)
    {
        asteroid->Update(deltaTime);
    }
    player->MoveStep(deltaTime);
}

void Render()
{
    sre::RenderPass renderPass = sre::RenderPass::create()
                                     .withCamera(camera)
                                     .withClearColor(true, {.3f, .3f, 1, 1})
                                     .build();
    sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();
    for (auto asteroid : asteroids)
    {
        asteroid->Render(atlas, spriteBatchBuilder);
    }

    player->Render(atlas, spriteBatchBuilder);

    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);
}
