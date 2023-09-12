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
    int pos_x;
    int pos_y;
    MoveDirection currDir = RIGHT;
};
