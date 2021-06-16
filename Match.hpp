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
    std::vector<sf::RectangleShape> boardRects;

    int rollDice();
};

#endif