#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(int id)
{
    data = new UserData(id);
    name = data->getName();
    data->incGames();
    finished = false;
    won = false;
}

HumanPlayer::~HumanPlayer()
{
    // increase victories number if won a match
    if (won)
    {
        data->incVicts();
    }
    delete data;
}

void HumanPlayer::makeMove(std::vector<int> &positions, int id, int delta) {};