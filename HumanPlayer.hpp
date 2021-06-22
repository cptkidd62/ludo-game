#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "Player.hpp"

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::wstring namestr);
    void makeMove(std::vector<int> &positions, int id, int delta);

protected:
};

#endif