#include <iostream>
#include <chrono>
#include <random>
#include <tuple>

#include "ITUGames.h"
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
#define TARGETFPS 60

int currX = 20;
int currY = 10;

std::chrono::time_point<std::chrono::steady_clock> prevEnd = std::chrono::steady_clock::now();

int main()
{
    std::srand(std::time(nullptr));
    ITUGames::Console::InitScreenForRendering();

    while (true)
    {
        ProcessEvents();
        Update();
        Render();
        ITUGames::Console::InitScreenForRendering();
        auto timings = GatherTimings();
        PrintInfo(std::get<0>(timings), std::get<1>(timings));
    }

    return 0;
}

std::tuple<std::chrono::duration<double>, std::chrono::duration<double>> GatherTimings()
{
    std::chrono::time_point<std::chrono::steady_clock> compute_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_compute = compute_end - prevEnd;
    ITUGames::Utils::PreciseSleep(std::chrono::duration<double>(1.0 / TARGETFPS - time_compute.count()));
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_elapsed = now - prevEnd;
    prevEnd = now;
    return std::make_tuple(time_elapsed, time_compute);
}

void PrintInfo(std::chrono::duration<double> time_elapsed, std::chrono::duration<double> time_compute)
{
    ITUGames::Console::GotoTop();
    ITUGames::Console::PrintStr("Frame time: " + std::to_string(time_elapsed.count() * 1000) + " ms\n");
    ITUGames::Console::PrintStr("FPS: " + std::to_string(1.0 / time_elapsed.count()) + "\n");
    ITUGames::Console::PrintStr("Compute time:" + std::to_string(time_compute.count() * 1000) + " ms\n");
    ITUGames::Console::PrintStr("Target FPS: " + std::to_string(TARGETFPS) + " (" + std::to_string(1000.0 / TARGETFPS) + " ms)\n");
}

void ProcessEvents()
{
    unsigned char buttonPressed = ITUGames::Console::GetCharacter(false);
    switch (buttonPressed)
    {
    case ITUGames::Console::KEY_W:
        currY--;
        break;
    case ITUGames::Console::KEY_S:
        currY++;
        break;
    case ITUGames::Console::KEY_D:
        currX++;
        break;
    case ITUGames::Console::KEY_A:
        currX--;
        break;
    case '\033':
        getch();
        switch (getch())
        {
        case 65:
            currY--;
            break;
        case 66:
            currY++;
            break;
        case 67:
            currX++;
            break;
        case 68:
            currX--;
            break;
        }
        break;
    default:
        break;
    }
}

void Update()
{
    if (currY < 5)
        currY = 5;
    if (currX < 0)
        currX = 0;
    ITUGames::Console::GotoCoords(currX, currY);
}

void Render()
{
    ITUGames::Console::PrintStr("0\n");
    ITUGames::Console::HideCursor();
}

void PrintInfo(std::chrono::time_point<std::chrono::steady_clock> time_start, std::chrono::time_point<std::chrono::steady_clock> time_end, std::chrono::time_point<std::chrono::steady_clock> compute_end)
{
    std::chrono::duration<double> time_elapsed = time_end - time_start;
    std::chrono::duration<double> time_compute = compute_end - time_start;
    ITUGames::Console::GotoTop();
    ITUGames::Console::PrintStr("Frame time: " + std::to_string(time_elapsed.count() * 1000) + "ms\n");
    ITUGames::Console::PrintStr("FPS: " + std::to_string(1.0 / time_elapsed.count()) + "\n");
    ITUGames::Console::PrintStr("Compute time:" + std::to_string(time_compute.count() * 1000) + "ms\n");
    ITUGames::Console::PrintStr("Target FPS: " + std::to_string(targetFPS) + " (" + std::to_string(1000.0 / targetFPS) + " ms)\n");
}

void ProcessEvents()
{
    unsigned char buttonPressed = ITUGames::Console::GetCharacter(false);
    switch (buttonPressed)
    {
    case ITUGames::Console::KEY_W:
        currY--;
        break;
    case ITUGames::Console::KEY_S:
        currY++;
        break;
    case ITUGames::Console::KEY_D:
        currX++;
        break;
    case ITUGames::Console::KEY_A:
        currX--;
        break;
    default:
        break;
    }
}

void Update()
{
    if (currY < 5)
        currY = 5;
    if (currX < 0)
        currX = 0;
    ITUGames::Console::GotoCoords(currX, currY);
}

void Render()
{
    ITUGames::Console::PrintStr("0\n");
    ITUGames::Console::HideCursor();
}

void LongComputation()
{
    // get a random number between 0.01 and 0.016
    double sleep_time = (10 + std::rand() % 6) / 1000.0;

    ITUGames::Utils::PreciseSleep(std::chrono::duration<double>(sleep_time));
}