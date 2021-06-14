#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include "Match.hpp"

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

    void menu();
    void startMatch();
};

#endif