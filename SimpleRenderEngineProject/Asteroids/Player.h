#include <deque>
#include <cstdlib>
#include "sre/SDLRenderer.hpp"

#define GAMEWIDTH 800
#define GAMEHEIGHT 600
#define ROWOFFSET 6

enum MoveDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player
{
public:
    Player();
    void HandleKeyPress(SDL_Event &event);
    void MoveStep(float deltaTime);
    void ApplyBound();
    bool HasLost();
    std::deque<glm::vec2> coordinates;
    MoveDirection currDir = RIGHT;
};
