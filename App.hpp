#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>

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
};

#endif