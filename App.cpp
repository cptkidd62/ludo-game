#include "App.hpp"

App::App()
{
    state = MENU;
    window.create(sf::VideoMode(200, 200), "Ludo Game");
}

void App::appLoop()
{
    while(state != EXIT)
    {
        switch (state)
        {
        case MENU:
            menu();
            break;
        
        default:
            break;
        }
    }
}

void App::menu()
{
    sf::Font font;
    font.loadFromFile("resources/AmaticSC-Bold.ttf");
    sf::Text title;
    title.setString("Ludo Game");
    title.setFont(font);
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Yellow);

    while (state == MENU)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                state = EXIT;
            }
        }

        window.clear();
        window.draw(title);
        window.display();
    }
}