#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include "Match.hpp"
#include "Stats.hpp"
#include "UsersList.hpp"
#include "UserData.hpp"

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
        STATS,
        EXIT
    };
    AppState state;
    sf::RenderWindow window;
    UsersList users;

    void menu();
    void startMatch();
    void showStats();
    int selectUser(int usrs[]);
    bool addUser();
};

#endif