#include "Player.hpp"

std::wstring Player::getName()
{
    return name;
}

bool Player::hasFinished()
{
    return finished;
}

void Player::setFinished()
{
    finished = true;
}

void Player::setWon()
{
    won = true;
}