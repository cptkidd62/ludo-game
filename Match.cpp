#include "Match.hpp"

Match::Match(std::initializer_list<int> ps)
{
    // initializing initial state variables
    playersNumber = 0;
    whoseTurn = 0;
    finishedTurn = false;
    finishedCount = 0;
    diceResult = 0;

    // creating players
    for (int i = 0; i < 4; i++)
    {
        if (*(ps.begin() + i) > 0)
        {
            players.push_back(new HumanPlayer(L"Człowiek " + std::to_wstring(i + 1)));
            playersNumber++;
        }
        else if (*(ps.begin() + i) < 0)
        {
            //TODO ai player
            playersNumber++;
        }
        else
        {
            players.push_back(nullptr);
            if (whoseTurn == i)
                whoseTurn++;
        }
    }

    // tiles coordinates
    sf::Vector2f boardTilesCoords[40] = {{4, 10}, {4, 9}, {4, 8}, {4, 7}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}, {0, 5}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {4, 0}, {5, 0}, {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {10, 5}, {10, 6}, {9, 6}, {8, 6}, {7, 6}, {6, 6}, {6, 7}, {6, 8}, {6, 9}, {6, 10}, {5, 10}};
    sf::Vector2f holdesCoords[16] = {{1, 8}, {2, 8}, {2, 9}, {1, 9}, {1, 1}, {2, 1}, {2, 2}, {1, 2}, {8, 1}, {9, 1}, {9, 2}, {8, 2}, {8, 8}, {9, 8}, {9, 9}, {8, 9}};
    sf::Vector2f homeCoords[16] = {{5, 9}, {5, 8}, {5, 7}, {5, 6}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {9, 5}, {8, 5}, {7, 5}, {6, 5}};

    // drawing values
    int edge = 68;
    int lineBoldness = 1;
    int offsetx = 100;
    int offsety = 10;

    // temporary rectangle and circle shape
    sf::RectangleShape tmp;
    tmp.setSize(sf::Vector2f(edge, edge));
    tmp.setFillColor(sf::Color::White);
    tmp.setOutlineColor(sf::Color::Black);
    tmp.setOutlineThickness(lineBoldness);
    sf::CircleShape circle;
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(lineBoldness);
    circle.setRadius(edge / 2);
    // adding shapes to vector
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
            circle.setFillColor(colors[i]);
            circle.setPosition(holdesCoords[i * 4 + j].x * (edge + 2 * lineBoldness) + offsetx, holdesCoords[i * 4 + j].y * (edge + 2 * lineBoldness) + offsety);
            piecesShape.push_back(circle);
        }
    }
    // initializing pieces position
    for (int i = 0; i < 16; i++)
    {
        pieces.push_back(-1);
    }
    state = PLAY;
}

void Match::runMatch(sf::RenderWindow &window)
{
    // loading font
    sf::Font font;
    font.loadFromFile("resources/AmaticSC-Bold.ttf");

    // creating texts
    sf::Text currentPlayer;
    currentPlayer.setString(players[whoseTurn]->getName() + L"'s turn");
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

    sf::Text button;
    button.setString("Roll the dice");
    button.setFont(font);
    button.setCharacterSize(30);
    button.setPosition(30, 170);
    button.setFillColor(sf::Color::Yellow);

    // game loop
    while (state != END)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // end game
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                state = END;
                break;
            }
            // check mouse button click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // check roll/next button
                if (button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    // roll the dice
                    if (diceResult == 0 && !finishedTurn)
                    {
                        diceResult = rollDice();
                        diceResultText.setString("Dice result: " + std::to_string(diceResult));
                        bool canMove = false;
                        for (int i = 0; i < 4; i++)
                        {
                            if (movePossible(4 * whoseTurn + i, diceResult))
                            {
                                canMove = true;
                                break;
                            }
                        }
                        if (!canMove)
                        {
                            diceResult = 0;
                            finishedTurn = true;
                            button.setString("Next");
                        }
                        break;
                    }
                    // move to next player
                    if (finishedTurn)
                    {
                        whoseTurn = (whoseTurn + 1) % playersNumber;
                        currentPlayer.setString(players[whoseTurn]->getName() + L"'s turn");
                        diceResultText.setString("");
                        finishedTurn = false;
                        button.setString("Roll the dice");
                    }
                }
                // check pieces
                for (int i = 0; i < 4; i++)
                {
                    if (diceResult != 0 && !finishedTurn && piecesShape[4 * whoseTurn + i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        if (movePossible(4 * whoseTurn + i, diceResult))
                        {
                            movePiece(4 * whoseTurn + i, diceResult);
                            if (diceResult != 6)
                            {
                                finishedTurn = true;
                                button.setString("Next");
                            }
                            diceResult = 0;
                        }
                        break;
                    }
                }
            }
        }

        // drawing
        window.clear();
        window.draw(currentPlayer);
        window.draw(diceResultText);
        window.draw(button);
        for (int i = 0; i < 40; i++)
        {
            window.draw(boardTiles[i]);
        }
        for (int i = 0; i < 16; i++)
        {
            window.draw(holderTiles[i]);
            window.draw(homeTiles[i]);
        }
        for (int i = 0; i < 16; i++)
        {
            window.draw(piecesShape[i]);
        }
        window.display();
    }
}

int Match::rollDice()
{
    srand(time(0));
    return rand() % 6 + 1;
}

bool Match::movePossible(int id, int delta)
{
    if (id / 4 == whoseTurn)
    {
        if (pieces[id] == -1)
        {
            if (delta == 6)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (pieces[whoseTurn * 4 + i] == 0)
                    {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        for (int i = 0; i < 16; i++)
        {
            if (pieces[id] + delta > 43 || (id / 4 == i / 4 && (pieces[id] + 10 * whoseTurn + delta) % 40 == (pieces[i] + 10 * (i / 4)) % 40 && pieces[i] > -1 && pieces[i] < 40))
                return false;
        }
        return true;
    }
    return false;
}

void Match::movePiece(int id, int delta)
{
    if (pieces[id] == -1)
    {
        pieces[id] = 0;
    }
    else
    {
        pieces[id] += delta;
        if (pieces[id] < 40)
        {
            for (int i = 0; i < 16; i++)
            {
                if (id / 4 != i / 4)
                {
                    if ((pieces[id] + 10 * whoseTurn) % 40 == (pieces[i] + 10 * (i / 4)) % 40)
                    {
                        pieces[i] = -1;
                        piecesShape[i].setPosition(holderTiles[i].getPosition());
                        break;
                    }
                }
            }
        }
    }
    if (pieces[id] > 39)
    {
        piecesShape[id].setPosition(homeTiles[whoseTurn * 4 + (pieces[id] - 39)].getPosition());
    }
    else
    {
        piecesShape[id].setPosition(boardTiles[(pieces[id] + 10 * whoseTurn) % 40].getPosition());
    }
}