#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(std::wstring namestr)
{
    name = namestr;
    finished = false;
}

void HumanPlayer::makeMove(std::vector<int> &positions, int id, int delta) {};