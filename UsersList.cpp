#include "UsersList.hpp"

UsersList::UsersList()
{
    loadFromFile();
}

UsersList::~UsersList()
{
    
}

bool UsersList::loadFromFile()
{
    std::wifstream file;
    file.open("data/users");
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