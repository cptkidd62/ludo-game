#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include <vector>
#include "Player.hpp"

class AIPlayer : public Player
{
public:
    virtual void makeMove(std::vector<int> &positions, int id, int delta) = 0;
};

#endif