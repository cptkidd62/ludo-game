#include "StatsView.hpp"

StatsView::StatsView(int id)
{
    font.loadFromFile("resources/AmaticSC-Bold.ttf");
    UserData data(id);
    name.setFont(font);
    name.setCharacterSize(30);
    name.setFillColor(sf::Color::Yellow);
    name.setString(data.name);
    name.setPosition(10, 10 + 40 * id);
    played.setFont(font);
    played.setCharacterSize(30);
    played.setFillColor(sf::Color::Yellow);
    played.setString("Total played: " + std::to_string(data.games));
    played.setPosition(200, 10 + 40 * id);
    won.setFont(font);
    won.setCharacterSize(30);
    won.setFillColor(sf::Color::Yellow);
    won.setString("Total won: " + std::to_string(data.victories));
    won.setPosition(450, 10 + 40 * id);
    percentage.setFont(font);
    percentage.setCharacterSize(30);
    percentage.setFillColor(sf::Color::Yellow);
    if (data.games == 0)
    {
        percentage.setString("");
    }
    else
    {
        percentage.setString("Rate: " + std::to_string(data.victories * 10 / data.games) + "%");
    }
    percentage.setPosition(700, 10 + 40 * id);
}

void StatsView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(name, states);
	target.draw(played, states);
	target.draw(won, states);
	target.draw(percentage, states);
}