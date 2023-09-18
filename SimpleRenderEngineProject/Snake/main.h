void LongComputation();

void Update(float deltaTime);

void Render();

void PrintInfo(std::chrono::duration<double> time_elapsed, std::chrono::duration<double> time_compute);

void ProcessEvents(SDL_Event &event);

void PrintBounds();
