#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player
{
public:
    std::wstring getName();

protected:
    std::wstring name;
};

#endif