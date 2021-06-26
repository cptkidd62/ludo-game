#ifndef USERDATA_HPP
#define USERDATA_HPP

#include <fstream>
#include "StatsView.hpp"

class UserData
{
    friend class StatsView;
public:
    UserData(int id);
    UserData(int id, std::wstring name);
    ~UserData();

    void incGames();
    void incVicts();
    std::wstring getName();

    bool loadFromFile();
    bool saveToFile();

private:
    int id;
    std::wstring name;
    int games;
    int victories;
};

#endif