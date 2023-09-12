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
}