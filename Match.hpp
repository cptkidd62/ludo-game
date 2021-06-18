#ifndef MATCH_HPP
#define MATCH_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

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
    std::vector<sf::RectangleShape> boardTiles;
    std::vector<sf::RectangleShape> holderTiles;
    std::vector<sf::RectangleShape> homeTiles;
    std::vector<sf::CircleShape> piecesShape;

    int rollDice();
};

#endif