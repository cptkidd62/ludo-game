#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

class Player
{
public:
    virtual ~Player() = 0;
    std::wstring getName();
    bool hasFinished();
    void setFinished();
    bool hasWon();
    void setWon();
    virtual void makeMove(std::vector<int> &positions, int id, int delta) = 0;

protected:
    std::wstring name;
    bool finished;
    bool won;
};

inline Player::~Player() {};

#endif