#include <deque>
#include <cstdlib>
#include "sre/SDLRenderer.hpp"

#define GAMEWIDTH 800
#define GAMEHEIGHT 600

enum MovementType
{
    CLOCKWISE,
    COUNTERCLOCKWISE,
    FORWARD,
    BACKWARD,
    NONE
};

class Player
{
public:
    Player(int x, int y);
    void HandleKeyPress(SDL_Event &event);
    void MoveStep(float deltaTime);
    void ApplyBound();
    float currHeading = 0;
    MovementType currMovement = NONE;
    glm::vec2 position;
};
