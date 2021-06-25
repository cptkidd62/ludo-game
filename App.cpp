#include "App.hpp"

App::App()
{
    state = MENU;
    window.create(sf::VideoMode(1000, 800), "Ludo Game");
}

void App::appLoop()
{
    while (state != EXIT)
    {
        switch (state)
        {
        case MENU:
            menu();
            break;

        case MATCH:
            startMatch();
            break;

        default:
            break;
        }
    }
}

void App::menu()
{
    sf::Font font;
    font.loadFromFile("resources/AmaticSC-Bold.ttf");
    sf::Text title;
    title.setString("Ludo Game");
    title.setFont(font);
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Yellow);

    while (state == MENU)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                state = EXIT;
                break;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                state = EXIT;
                break;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                state = MATCH;
                break;
            }
        }

        window.clear();
        window.draw(title);
        window.display();
    }
}

void App::startMatch()
{
    sf::Font font;
    font.loadFromFile("resources/AmaticSC-Bold.ttf");
    sf::Color colors[4] = {sf::Color::Yellow, sf::Color::Red, sf::Color::Blue, sf::Color::Green};
    int count[] = {1, 1, 1, 1};
    sf::Text title;
    title.setString("New Game");
    title.setFont(font);
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Yellow);
    sf::Text start;
    start.setString("Play");
    start.setFont(font);
    start.setCharacterSize(30);
    start.setFillColor(sf::Color::Yellow);
    start.setPosition(window.getSize().x / 2 - start.getGlobalBounds().width / 2, 720);
    std::vector<sf::Text> ptext[4];
    for (int i = 0; i < 4; i++)
    {
        sf::Text tmp;
        tmp.setFont(font);
        tmp.setCharacterSize(30);
        tmp.setFillColor(sf::Color::White);
        tmp.setString("Human");
        tmp.setPosition(60, 150 * (i + 1));
        ptext[i].push_back(tmp);
        tmp.setFillColor(colors[i]);
        tmp.setString("Computer");
        tmp.move(0, 40);
        ptext[i].push_back(tmp);
        tmp.setFillColor(sf::Color::White);
        tmp.setString("None");
        tmp.move(0, 40);
        ptext[i].push_back(tmp);
    }
    int list[] = {-1, -1, -1, -1};
    while (state == MATCH)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                state = EXIT;
                break;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                state = MENU;
                break;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (start.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && count[0] + count[1] + count[2] + count[3] > 1)
                {
                    Match match({list[0], list[1], list[2], list[3]});
                    match.runMatch(window);
                    state = MENU;
                    break;
                }
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (ptext[i][j].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                        {
                            ptext[i][j].setFillColor(colors[i]);
                            if (j == 0)
                            {
                                selectUser(list);
                                list[i] = i + 1;
                                count[i] = 1;
                            }
                            else if (j == 1)
                            {
                                list[i] = -1;
                                count[i] = 1;
                            }
                            else
                            {
                                list[i] = 0;
                                count[i] = 0;
                            }
                            for (int k = 0; k < 3; k++)
                            {
                                if (k != j)
                                {
                                    ptext[i][k].setFillColor(sf::Color::White);
                                    if (k == 0)
                                    {
                                        ptext[i][k].setString("Human");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(title);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                window.draw(ptext[i][j]);
            }
        }
        window.draw(start);
        window.display();
    }
}

int App::selectUser(int usrs[])
{
    sf::Font font;
    font.loadFromFile("resources/AmaticSC-Bold.ttf");
    std::vector<sf::Text> buttons;
    sf::Text tmp;
    tmp.setFont(font);
    tmp.setCharacterSize(30);
    tmp.setFillColor(sf::Color::Yellow);
    tmp.setPosition(60, 10);
    for (int i = 0; i < users.size; i++)
    {
        tmp.setString(users.list[i]);
        tmp.move(0, 50);
        buttons.push_back(tmp);
    }
    tmp.setString("Add new");
    tmp.move(0, 50);
    buttons.push_back(tmp);
    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                return 0;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                addUser();
            }
        }

        window.clear();
        for (auto btn : buttons)
        {
            window.draw(btn);
        }
        window.display();
    }
}

void App::addUser()
{
    sf::Font font;
    font.loadFromFile("resources/AmaticSC-Bold.ttf");
    sf::String str(L"");
    sf::Text name;
    name.setFont(font);
    name.setCharacterSize(30);
    name.setFillColor(sf::Color::Yellow);
    name.setString(str);
    name.setPosition(100, 100);
    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                users.list[users.size] = str.toWideString();
                users.size++;
                return;
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode >= 32 && event.text.unicode <= 383)
                {
                    str.insert(str.getSize(), static_cast<wchar_t>(event.text.unicode));
                }
                if (event.text.unicode == 8)
                {
                    if (str.getSize() > 0)
                    {
                        str.erase(str.getSize() - 1, 1);
                    }
                }
                name.setString(str);
            }
        }

        window.clear();
        window.draw(name);
        window.display();
    }
}