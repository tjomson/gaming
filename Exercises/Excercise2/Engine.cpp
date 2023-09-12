#include "Engine.h"

#include <chrono>

Engine::Engine()
{
    compute_end = std::chrono::steady_clock::now();
}

void Engine::StepLoop()
{
    compute_end = std::chrono::steady_clock::now();
    time_compute = compute_end - prevEnd;
    auto sleep_time = std::chrono::duration<double>(1.0 / TARGETFPS - time_compute.count());
    auto sleep_start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - sleep_start < sleep_time)
        ;
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    time_elapsed = now - prevEnd;
    prevEnd = now;
}
