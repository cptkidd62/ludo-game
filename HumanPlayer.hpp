#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "Player.hpp"
#include "UserData.hpp"

class HumanPlayer : public Player
{
public:
    HumanPlayer(int id);
    ~HumanPlayer();
    void makeMove(std::vector<int> &positions, int id, int delta);

protected:
    UserData *data;
};

#endif