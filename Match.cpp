#include "Match.hpp"

Match::Match()
{
    playersNumber = 4;
    whoseTurn = 1;
    state = PLAY;
}

void Match::runMatch(sf::RenderWindow &window)
{
    sf::Font font;
    font.loadFromFile("resources/AmaticSC-Bold.ttf");

    sf::Text currentPlayer;
    currentPlayer.setString("Player " + std::to_string(whoseTurn) + " turn");
    currentPlayer.setFont(font);
    currentPlayer.setCharacterSize(30);
    currentPlayer.setPosition(30, 30);
    currentPlayer.setFillColor(sf::Color::Yellow);

    sf::Text diceResultText;
    diceResultText.setString("");
    diceResultText.setFont(font);
    diceResultText.setCharacterSize(30);
    diceResultText.setPosition(30, 100);
    diceResultText.setFillColor(sf::Color::Yellow);

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
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                diceResultText.setString("Dice result: " + std::to_string(rollDice()));
                whoseTurn = whoseTurn % 4 + 1;
                currentPlayer.setString("Player " + std::to_string(whoseTurn) + " turn");
                break;
            }
        }

        window.clear();
        window.draw(currentPlayer);
        window.draw(diceResultText);
        window.display();
    }
}

int Match::rollDice()
{
    srand(time(0));
    return rand() % 6 + 1;
}