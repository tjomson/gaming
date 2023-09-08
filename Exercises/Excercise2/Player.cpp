#include "Player.h"
#include "ITUGames.h"

Player::Player()
{
    pos_x = std::rand() % ITUGames::Console::GetTerminalWidth();
    pos_y = std::rand() % ITUGames::Console::GetTerminalHeight();
}

void Player::MoveUp()
{
    pos_y--;
}

void Player::MoveDown()
{
    pos_y++;
}

void Player::MoveRight()
{
    pos_x++;
}

void Player::MoveLeft()
{
    pos_x--;
}