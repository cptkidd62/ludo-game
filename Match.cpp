#include "Match.hpp"

Match::Match()
{
    state = PLAY;
}

void Match::runMatch(sf::RenderWindow &window)
{
    sf::Font font;
    font.loadFromFile("resources/AmaticSC-Bold.ttf");
    sf::Text title;
    title.setString("Ludo Game - let's play");
    title.setFont(font);
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Yellow);

    while (state != END)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                state = END;
                break;
            }
        }

        window.clear();
        window.draw(title);
        window.display();
    }
}