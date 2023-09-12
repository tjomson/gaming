#include <iostream>
#include <chrono>
#include <random>
#include <tuple>

#include "ITUGames.h"
#include "Engine.h"
#include "Player.h"
#pragma region Engine State

#pragma endregion // Engine State

#pragma region Game State

/**
 * If you are unsure how to organize the additional variables you will need for the exercise, just dump them here.We will address this in future lectures
 * In the meantime, a good approach is to sort them and put the ones that relate to the same thing togheter
 * - is this variable part of the game? Of the engine? ...
 * - is it about input? Player state? Logging? ...
 * And so on. Are some of those questions conflicting with each other? Yep, architecturing code is hard, but we'll get a hang of it.
 */

#pragma endregion // Game State

#include "main.h"

auto player = new Player();

int main()
{
    std::srand(std::time(nullptr));
    ITUGames::Console::InitScreenForRendering();
    auto engine = new Engine();
    int framesSinceStep = 0;

    while (true)
    {
        ProcessEvents();
        //        Update();
        Render();
        ITUGames::Console::InitScreenForRendering();
        engine->StepLoop();
        framesSinceStep++;
        if (framesSinceStep == FRAME_SKIPS_BETWEEN_STEPS)
        {
            framesSinceStep = 0;
            player->MoveStep();
        }
        PrintInfo(engine->time_elapsed, engine->time_compute);
    }

    return 0;
}

void PrintInfo(std::chrono::duration<double> time_elapsed, std::chrono::duration<double> time_compute)
{
    ITUGames::Console::GotoTop();
    ITUGames::Console::PrintStr("Frame time: " + std::to_string(time_elapsed.count() * 1000) + " ms\n");
    ITUGames::Console::PrintStr("FPS: " + std::to_string(1.0 / time_elapsed.count()) + "\n");
    ITUGames::Console::PrintStr("Compute time:" + std::to_string(time_compute.count() * 1000) + " ms\n");
    ITUGames::Console::PrintStr("Target FPS: " + std::to_string(TARGETFPS) + " (" + std::to_string(1000.0 / TARGETFPS) + " ms)\n");
    ITUGames::Console::PrintStr("snake front: " + std::to_string(player->coordinates.front().x) + " " + std::to_string(player->coordinates.front().y));
}

void ProcessEvents()
{
    unsigned char buttonPressed = ITUGames::Console::GetCharacter(false);
    switch (buttonPressed)
    {
    case ITUGames::Console::KEY_W:
        player->MoveUp();
        break;
    case ITUGames::Console::KEY_S:
        player->MoveDown();
        break;
    case ITUGames::Console::KEY_D:
        player->MoveRight();
        break;
    case ITUGames::Console::KEY_A:
        player->MoveLeft();
        break;
    case '\033':
        getch();
        switch (getch())
        {
        case 65:
            player->MoveUp();
            break;
        case 66:
            player->MoveDown();
            break;
        case 67:
            player->MoveRight();
            break;
        case 68:
            player->MoveLeft();
            break;
        }
        break;
    default:
        break;
    }
}

void Update()
{
    //    ITUGames::Console::GotoCoords(player->pos_x, player->pos_y);
}

void Render()
{
    for (auto coord : player->coordinates)
    {
        ITUGames::Console::GotoCoords(coord.x, coord.y);
        ITUGames::Console::PrintStr("O");
    }
    ITUGames::Console::PrintStr("\n");
    ITUGames::Console::HideCursor();
}

void LongComputation()
{
    // get a random number between 0.01 and 0.016
    double sleep_time = (10 + std::rand() % 6) / 1000.0;

    ITUGames::Utils::PreciseSleep(std::chrono::duration<double>(sleep_time));
}