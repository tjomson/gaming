#include "Player.h"
#include "ITUGames.h"

Player::Player()
{
    coordinates.push_front({20, 10});
    coordinates.push_front({19, 10});
    coordinates.push_front({18, 10});
    frame_skips = 15;
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

void Player::SetNewFood()
{
    int food_x = (std::rand() % GAMEWIDTH - 1) + 1;
    int food_y = (std::rand() % GAMEHEIGHT) + ROWOFFSET;
    food_pos = {food_x, food_y};
}

void Player::MoveStep()
{
    auto prevFirst = coordinates.front();
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
    if (coordinates.front().x != food_pos.x || coordinates.front().y != food_pos.y)
        coordinates.pop_back();
    else
    {
        SetNewFood();
        frame_skips *= 0.9;
    }
    ApplyBound();
}