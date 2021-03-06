#include "UsersList.hpp"

UsersList::UsersList()
{
    loadFromFile();
}

UsersList::~UsersList()
{
    saveToFile();
}

bool UsersList::loadFromFile()
{
    std::wifstream file;
    file.open("users");
    if (file.good())
    {
        while (!file.eof())
        {
            int id;
            std::wstring str;
            file >> id;
            file >> str;
            list[id] = str;
            size++;
        }
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

bool UsersList::saveToFile()
{
    std::wofstream file;
    file.open("users");
    if (file.good())
    {
        for (auto p : list)
        {
            file << ' ' << p.first << ' ' << p.second;
        }
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}