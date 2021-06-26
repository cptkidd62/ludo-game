#ifndef STATSVIEW_HPP
#define STATSVIEW_HPP

#include <SFML/Graphics.hpp>
#include "UserData.hpp"

class StatsView : public sf::Drawable
{
public:
    StatsView(int id);

private:
    sf::Font font;
    sf::Text name;
    sf::Text played;
    sf::Text won;
    sf::Text percentage;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif