#include "Match.hpp"

Match::Match()
{
    playersNumber = 4;
    whoseTurn = 1;
    sf::Vector2f coords[40] = {{4, 10}, {4, 9}, {4, 8}, {4, 7}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}, {0, 5}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {4, 0}, {5, 0}, {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {10, 5}, {10, 6}, {9, 6}, {8, 6}, {7, 6}, {6, 6}, {6, 7}, {6, 8}, {6, 9}, {6, 10}, {5, 10}};
    int edge = 70;
    int offsetx = 100;
    int offsety = 10;
    sf::RectangleShape tmp;
    tmp.setSize(sf::Vector2f(edge, edge));
    tmp.setFillColor(sf::Color::White);
    tmp.setOutlineColor(sf::Color::Red);
    tmp.setOutlineThickness(2);
    for (int i = 0; i < 40; i++)
    {
        tmp.setPosition(coords[i].x * edge + offsetx, coords[i].y * edge + offsety);
        boardRects.push_back(tmp);
    }
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
        for (int i = 0; i < 40; i++)
        {
            window.draw(boardRects[i]);
        }
        window.display();
    }
}

int Match::rollDice()
{
    srand(time(0));
    return rand() % 6 + 1;
}