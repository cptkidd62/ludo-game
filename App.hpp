#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include "Match.hpp"
#include "UsersList.hpp"

class App
{
public:
    App();
    void appLoop();

private:
    enum AppState
    {
        MENU,
        MATCH,
        EXIT
    };
    AppState state;
    sf::RenderWindow window;
    UsersList users;

    void menu();
    void startMatch();
    int selectUser(int usrs[]);
    bool addUser();
};

#endif