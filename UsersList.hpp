#ifndef USERSLIST_HPP
#define USERSLIST_HPP

#include <map>
#include <fstream>

class UsersList
{
public:
    UsersList();
    ~UsersList();

    std::map<int, std::wstring> list;
    int size = 0;

    bool loadFromFile();
    bool saveToFile();
};

#endif