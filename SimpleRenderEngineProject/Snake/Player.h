#include <deque>

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
    bool HasLost();
    double frame_skips;
    Coordinate food_pos;
    std::deque<Coordinate> coordinates;
    MoveDirection currDir = RIGHT;
};
