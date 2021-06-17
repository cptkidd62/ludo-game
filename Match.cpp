#include "Match.hpp"

Match::Match()
{
    playersNumber = 4;
    whoseTurn = 1;
    finishedCount = 0;
    sf::Vector2f boardTilesCoords[40] = {{4, 10}, {4, 9}, {4, 8}, {4, 7}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}, {0, 5}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {4, 0}, {5, 0}, {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {10, 5}, {10, 6}, {9, 6}, {8, 6}, {7, 6}, {6, 6}, {6, 7}, {6, 8}, {6, 9}, {6, 10}, {5, 10}};
    sf::Vector2f holdesCoords[16] = {{1, 8}, {2, 8}, {2, 9}, {1, 9}, {1, 1}, {2, 1}, {2, 2}, {1, 2}, {8, 1}, {9, 1}, {9, 2}, {8, 2}, {8, 8}, {9, 8}, {9, 9}, {8, 9}};
    sf::Vector2f homeCoords[16] = {{5, 9}, {5, 8}, {5, 7}, {5, 6}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {9, 5}, {8, 5}, {7, 5}, {6, 5}};
    sf::Color colors[4] = {sf::Color::Yellow, sf::Color::Red, sf::Color::Blue, sf::Color::Green};
    int edge = 68;
    int lineBoldness = 1;
    int offsetx = 100;
    int offsety = 10;
    sf::RectangleShape tmp;
    tmp.setSize(sf::Vector2f(edge, edge));
    tmp.setFillColor(sf::Color::White);
    tmp.setOutlineColor(sf::Color::Black);
    tmp.setOutlineThickness(lineBoldness);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            tmp.setPosition(boardTilesCoords[i * 10 + j].x * (edge + 2 * lineBoldness) + offsetx, boardTilesCoords[i * 10 + j].y * (edge + 2 * lineBoldness) + offsety);
            boardTiles.push_back(tmp);
        }
        for (int j = 0; j < 4; j++)
        {
            tmp.setFillColor(colors[i]);
            tmp.setPosition(homeCoords[i * 4 + j].x * (edge + 2 * lineBoldness) + offsetx, homeCoords[i * 4 + j].y * (edge + 2 * lineBoldness) + offsety);
            homeTiles.push_back(tmp);
            tmp.setOutlineColor(colors[i]);
            tmp.setFillColor(sf::Color::White);
            tmp.setPosition(holdesCoords[i * 4 + j].x * (edge + 2 * lineBoldness) + offsetx, holdesCoords[i * 4 + j].y * (edge + 2 * lineBoldness) + offsety);
            holderTiles.push_back(tmp);
            tmp.setOutlineColor(sf::Color::Black);
        }
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
                whoseTurn = whoseTurn % playersNumber + 1;
                currentPlayer.setString("Player " + std::to_string(whoseTurn) + " turn");
                break;
            }
        }

        window.clear();
        window.draw(currentPlayer);
        window.draw(diceResultText);
        for (int i = 0; i < 40; i++)
        {
            window.draw(boardTiles[i]);
        }
        for (int i = 0; i < 16; i++)
        {
            window.draw(holderTiles[i]);
            window.draw(homeTiles[i]);
        }
        window.display();
    }
}

int Match::rollDice()
{
    srand(time(0));
    return rand() % 6 + 1;
}