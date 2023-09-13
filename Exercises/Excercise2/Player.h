#include <deque>

#define GAMEWIDTH 80
#define GAMEHEIGHT 30
#define ROWOFFSET 6

enum MoveDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Coordinate
{
    int x;
    int y;
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
    Coordinate food_pos;
    std::deque<Coordinate> coordinates;
    MoveDirection currDir = RIGHT;
};
