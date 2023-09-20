#include <deque>
#include <cstdlib>
#include "sre/SDLRenderer.hpp"

#define GAMEWIDTH 50
#define GAMEHEIGHT 30
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
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    void MoveStep();
    void ApplyBound();
    void SetNewFood();
    bool HasLost();
    double frame_skips;
    glm::vec2 food_pos;
    std::deque<glm::vec2> coordinates;
    MoveDirection currDir = RIGHT;
};
