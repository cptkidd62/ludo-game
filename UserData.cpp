#include "UserData.hpp"

UserData::UserData(int id)
{
    this->id = id;
    loadFromFile();
}

UserData::UserData(int id, std::wstring name)
{
    this->id = id;
    this->name = name;
    games = 0;
    victories = 0;
    saveToFile();
}

UserData::~UserData()
{
    saveToFile();
}

void UserData::incGames()
{
    games++;
}

void UserData::incVicts()
{
    victories++;
}

std::wstring UserData::getName()
{
    return name;
}

bool UserData::loadFromFile()
{
    std::wifstream file;
    file.open(std::to_string(id) + ".ud");
    if (file.good())
    {
        file >> name;
        file >> games;
        file >> victories;
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

bool UserData::saveToFile()
{
    std::wofstream file;
    file.open(std::to_string(id) + ".ud");
    if (file.good())
    {
        file << name << " " << games << " " << victories;
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}