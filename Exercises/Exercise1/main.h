void LongComputation();

void Update();

void Render();

void PrintInfo(std::chrono::duration<double> time_elapsed, std::chrono::duration<double> time_compute);

void ProcessEvents();

std::tuple<std::chrono::duration<double>, std::chrono::duration<double>> StepLoop();
