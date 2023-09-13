#include <deque>

#define GAMEWIDTH 80
#define GAMEHEIGHT 30
#define ROWOFFSET 5

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
    std::deque<Coordinate> coordinates;
    MoveDirection currDir = RIGHT;
};
