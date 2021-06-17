#include "App.hpp"

App::App()
{
    state = MENU;
    window.create(sf::VideoMode(1000, 800), "Ludo Game");
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

        case MATCH:
            startMatch();
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
                break;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                state = EXIT;
                break;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                state = MATCH;
                break;
            }
        }

        window.clear();
        window.draw(title);
        window.display();
    }
}

void App::startMatch()
{
    Match match;
    match.runMatch(window);
    state = MENU;
}