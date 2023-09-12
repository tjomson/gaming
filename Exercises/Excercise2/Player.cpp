#include "Player.h"
#include "ITUGames.h"

Player::Player()
{
    pos_x = 20;
    pos_y = 10;
}

void Player::MoveUp()
{
    currDir = UP;
}

void Player::MoveDown()
{
    currDir = DOWN;
}

void Player::MoveRight()
{
    currDir = RIGHT;
}

void Player::MoveLeft()
{
    currDir = LEFT;
}