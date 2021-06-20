#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player
{
public:
    std::wstring getName();
    bool hasFinished();
    void setFinished();

protected:
    std::wstring name;
    bool finished;
};

#endif