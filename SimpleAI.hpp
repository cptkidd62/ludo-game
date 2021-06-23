#ifndef SIMPLEAI_HPP
#define SIMPLEAI_HPP

#include "AIPlayer.hpp"

class SimpleAIPlayer : public AIPlayer
{
public:
    SimpleAIPlayer();
    void makeMove(std::vector<int> &positions, int id, int delta);
};

#endif