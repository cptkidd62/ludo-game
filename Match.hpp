#ifndef MATCH_HPP
#define MATCH_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "HumanPlayer.hpp"

class Match
{
public:
    Match(std::initializer_list<int> ps);

    void runMatch(sf::RenderWindow &window);

private:
    enum MatchState
    {
        PLAY,
        END
    };
    MatchState state;
    int playersNumber;
    int whoseTurn;
    bool finishedTurn;
    int finishedCount;
    int diceResult;
    std::vector<Player *> players;
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

template <typename Base, typename T>
inline bool instanceof (const T *)
{
    return std::is_base_of<Base, T>::value;
}

#endif