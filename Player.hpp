#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

class Player
{
public:
    std::wstring getName();
    bool hasFinished();
    void setFinished();
    virtual void makeMove(std::vector<int> &positions, int id, int delta) = 0;

protected:
    std::wstring name;
    bool finished;
};

#endif