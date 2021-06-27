#include "Stats.hpp"

Stats::Stats(const UsersList &users)
{
    // create statsviews from user data
    for (auto u : users.list)
    {
        StatsView view(u.first);
        panels.push_back(view);
    }
}

void Stats::runStats(sf::RenderWindow &window)
{
    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // return
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                return;
            }
        }

        window.clear();
        for (auto p : panels)
        {
            window.draw(p);
        }
        window.display();
    }
}