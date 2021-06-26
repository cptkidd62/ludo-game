#ifndef STATS_HPP
#define STATS_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "StatsView.hpp"
#include "UsersList.hpp"
#include "UserData.hpp"

class Stats
{
public:
    Stats(const UsersList &users);

    void runStats(sf::RenderWindow &window);

private:
    std::vector<StatsView> panels;
};

#endif