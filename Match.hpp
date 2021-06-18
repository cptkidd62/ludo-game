#ifndef MATCH_HPP
#define MATCH_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Match
{
public:
    Match();

    void runMatch(sf::RenderWindow &window);

private:
    enum MatchState {PLAY, END};
    MatchState state;
    int playersNumber;
    int whoseTurn;
    int finishedCount;
    int diceResult;
    std::vector<sf::RectangleShape> boardTiles;
    std::vector<sf::RectangleShape> holderTiles;
    std::vector<sf::RectangleShape> homeTiles;
    std::vector<sf::CircleShape> piecesShape;
    std::vector<int> pieces;

    const sf::Color colors[4] = {sf::Color::Yellow, sf::Color::Red, sf::Color::Blue, sf::Color::Green};

    int rollDice();
    bool movePossible(int id, int delta);
    void movePiece(int id, int delta);
};

#endif