#include "Player.h"
#include "ITUGames.h"

Player::Player()
{
    coordinates.push_front({20, 10});
    coordinates.push_front({19, 10});
    coordinates.push_front({18, 10});
}

void Player::MoveUp()
{
    if (currDir != DOWN)
        currDir = UP;
}

void Player::MoveDown()
{
    if (currDir != UP)
        currDir = DOWN;
}

void Player::MoveRight()
{
    if (currDir != LEFT)
        currDir = RIGHT;
}

void Player::MoveLeft()
{
    if (currDir != RIGHT)
        currDir = LEFT;
}

void Player::ApplyBound()
{
    auto front = coordinates.front();
    coordinates.pop_front();
    if (front.x >= GAMEWIDTH)
        front.x = 2;
    else if (front.x <= 1)
        front.x = GAMEWIDTH - 1;
    if (front.y >= GAMEHEIGHT + ROWOFFSET)
        front.y = ROWOFFSET + 1;
    else if (front.y < ROWOFFSET + 1)
        front.y = GAMEHEIGHT + ROWOFFSET - 1;
    coordinates.push_front({front.x, front.y});
}

void Player::MoveStep()
{
    auto prevFirst = coordinates.front();
    coordinates.pop_back();
    switch (currDir)
    {
    case UP:
        coordinates.push_front({prevFirst.x, prevFirst.y - 1});
        break;
    case DOWN:
        coordinates.push_front({prevFirst.x, prevFirst.y + 1});
        break;
    case LEFT:
        coordinates.push_front({prevFirst.x - 1, prevFirst.y});
        break;
    case RIGHT:
        coordinates.push_front({prevFirst.x + 1, prevFirst.y});
        break;
    }
    ApplyBound();
}