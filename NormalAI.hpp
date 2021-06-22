#ifndef NORMALAI_HPP
#define NORMALAI_HPP

#include "AIPlayer.hpp"

class NormalAIPlayer : public AIPlayer
{
public:
    NormalAIPlayer();
    void makeMove(std::vector<int> &positions, int id, int delta);
};

#endif