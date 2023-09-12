#include <deque>

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
    std::deque<Coordinate> coordinates;

    MoveDirection currDir = RIGHT;
};
