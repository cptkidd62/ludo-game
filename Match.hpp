#ifndef MATCH_HPP
#define MATCH_HPP

#include <SFML/Graphics.hpp>

class Match
{
public:
    Match();

    void runMatch(sf::RenderWindow &window);

private:
    enum MatchState {PLAY, END};
    MatchState state;

};

#endif