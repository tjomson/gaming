#pragma once

#include <chrono>

#define TARGETFPS 60
#define FRAME_SKIPS_BETWEEN_STEPS 20

class Engine
{
public:
    Engine();
    std::chrono::time_point<std::chrono::steady_clock> compute_end;
    std::chrono::duration<double> time_compute;
    std::chrono::duration<double> time_elapsed;
    std::chrono::time_point<std::chrono::steady_clock> prevEnd;
    void StepLoop();
};
