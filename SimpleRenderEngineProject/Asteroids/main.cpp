#include <iostream>
#include <chrono>
#include <random>
#include <tuple>

#include "Player.h"
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#pragma region Engine State
#pragma endregion
#pragma region Game State
#pragma endregion
#include "main.h"

auto player = new Player();
glm::vec2 window_size = glm::vec2(GAMEWIDTH, GAMEHEIGHT);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;
sre::Sprite sprite;

int main()
{
    renderer.frameRender = Render;
    renderer.frameUpdate = Update;
    renderer.keyEvent = ProcessEvents;
    renderer.setWindowSize(window_size);
    renderer.init();
    camera.setWindowCoordinates();
    atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");
    sprite = atlas->get("meteorGrey_big4.png");
    sprite.setPosition(window_size / 2.0f);
    renderer.startEventLoop();
}

void ProcessEvents(SDL_Event &event)
{
    player->HandleKeyPress(event);
}

void Update(float deltaTime)
{
    player->MoveStep(deltaTime);
}

void Render()
{
    sre::RenderPass renderPass = sre::RenderPass::create()
                                     .withCamera(camera)
                                     .withClearColor(true, {.3f, .3f, 1, 1})
                                     .build();
    sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();

    for (auto coord : player->coordinates)
    {
        sre::Sprite snakePart = atlas->get("playerShip1_green.png");
        snakePart.setPosition(coord);
        spriteBatchBuilder.addSprite(snakePart);
    }

    spriteBatchBuilder.addSprite(sprite);
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);
}
