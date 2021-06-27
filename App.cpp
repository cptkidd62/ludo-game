#include "App.hpp"

App::App()
{
    state = MENU;
    // create window
    window.create(sf::VideoMode(1000, 800), "Ludo Game");
    // load font
    font.loadFromFile("resources/AmaticSC-Bold.ttf");
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

        case STATS:
            showStats();
            break;

        default:
            break;
        }
    }
}

void App::menu()
{
    // game title
    sf::Text title;
    title.setString("Ludo Game");
    title.setFont(font);
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100);

    sf::Text newGame;
    newGame.setString("Play");
    newGame.setFont(font);
    newGame.setCharacterSize(50);
    newGame.setFillColor(sf::Color::Yellow);
    newGame.setPosition(window.getSize().x / 2 - newGame.getGlobalBounds().width / 2, 300);

    sf::Text stat;
    stat.setString("Statistics");
    stat.setFont(font);
    stat.setCharacterSize(50);
    stat.setFillColor(sf::Color::Yellow);
    stat.setPosition(window.getSize().x / 2 - stat.getGlobalBounds().width / 2, 400);

    sf::Text quit;
    quit.setString("Exit");
    quit.setFont(font);
    quit.setCharacterSize(50);
    quit.setFillColor(sf::Color::Yellow);
    quit.setPosition(window.getSize().x / 2 - quit.getGlobalBounds().width / 2, 500);

    while (state == MENU)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close app - close button
            if (event.type == sf::Event::Closed)
            {
                window.close();
                state = EXIT;
                break;
            }
            // close app - escape
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                state = EXIT;
                break;
            }
            // run match
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                state = MATCH;
                break;
            }
            // open stats window
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                state = STATS;
                break;
            }
            // clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // run match
                if (newGame.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    state = MATCH;
                    break;
                }
                // open stats window
                if (stat.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    state = STATS;
                    break;
                }
                // exit
                if (quit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    state = EXIT;
                    break;
                }
            }
        }

        window.clear();
        window.draw(title);
        window.draw(newGame);
        window.draw(stat);
        window.draw(quit);
        window.display();
    }
}

void App::startMatch()
{
    // colors table
    sf::Color colors[4] = {sf::Color::Yellow, sf::Color::Red, sf::Color::Blue, sf::Color::Green};

    // table - 0 is void, 1 is player
    int count[] = {1, 1, 1, 1};

    // sf texts
    sf::Text quit;
    quit.setString("Back");
    quit.setFont(font);
    quit.setCharacterSize(50);
    quit.setFillColor(sf::Color::Yellow);
    quit.setPosition(600, 500);
    sf::Text start;
    start.setString("Play");
    start.setFont(font);
    start.setCharacterSize(50);
    start.setFillColor(sf::Color::Yellow);
    start.setPosition(600, 300);

    // table of 4 vectors of 3 texts each - buttons for selecting player
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

    // table: < 0 - computer, 0 - null, > 0 - human
    int list[] = {-1, -1, -1, -1};

    // window loop
    while (state == MATCH)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close app
            if (event.type == sf::Event::Closed)
            {
                window.close();
                state = EXIT;
                break;
            }
            // return to menu - escape
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                state = MENU;
                break;
            }
            // clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // start button - start match
                if (start.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && count[0] + count[1] + count[2] + count[3] > 1)
                {
                    Match match({list[0], list[1], list[2], list[3]});
                    match.runMatch(window);
                    state = MENU;
                    break;
                }
                // return to menu
                if (quit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    state = MENU;
                    break;
                }
                // check all player texts
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (ptext[i][j].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                        {
                            // human
                            if (j == 0)
                            {
                                int res = selectUser(list);
                                if (res > -1)
                                {
                                    list[i] = res + 1;
                                    count[i] = 1;
                                    ptext[i][0].setString(users.list[res]);
                                    ptext[i][1].setFillColor(sf::Color::White);
                                    ptext[i][2].setFillColor(sf::Color::White);
                                    ptext[i][j].setFillColor(colors[i]);
                                }
                            }
                            // computer
                            else if (j == 1)
                            {
                                srand(time(0));
                                list[i] = -(rand() % 2 + 1);
                                count[i] = 1;
                                ptext[i][0].setString("Human");
                                ptext[i][0].setFillColor(sf::Color::White);
                                ptext[i][2].setFillColor(sf::Color::White);
                                ptext[i][j].setFillColor(colors[i]);
                            }
                            // none
                            else
                            {
                                list[i] = 0;
                                count[i] = 0;
                                ptext[i][0].setString("Human");
                                ptext[i][0].setFillColor(sf::Color::White);
                                ptext[i][1].setFillColor(sf::Color::White);
                                ptext[i][j].setFillColor(colors[i]);
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(quit);
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

void App::showStats()
{
    Stats stats(users);
    stats.runStats(window);
    state = MENU;
}

int App::selectUser(int usrs[])
{
    // vector for buttons
    std::vector<sf::Text> buttons;
    sf::Text tmp;
    tmp.setFont(font);
    tmp.setCharacterSize(50);
    tmp.setFillColor(sf::Color::Yellow);
    tmp.setPosition(100, 30);
    for (int i = 0; i < users.size; i++)
    {
        tmp.setString(users.list[i]);
        tmp.move(0, 70);
        buttons.push_back(tmp);
    }
    tmp.setString("Add new");
    tmp.move(0, 70);
    buttons.push_back(tmp);

    sf::Text back;
    back.setFont(font);
    back.setCharacterSize(50);
    back.setFillColor(sf::Color::Yellow);
    back.setString("Back");
    back.setPosition(800, 50);

    // window loop
    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // return with no selection - escape
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                return -1;
            }
            // add new user
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                if (addUser())
                {
                    buttons[buttons.size() - 1].setString(users.list[buttons.size() - 1]);
                    tmp.setString("Add new");
                    tmp.move(0, 70);
                    buttons.push_back(tmp);
                }
            }
            // clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // select one of existing users
                for (int i = 0; i < (int)buttons.size() - 1; i++)
                {
                    if (buttons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        if (i + 1 != usrs[0] && i + 1 != usrs[1] && i + 1 != usrs[2] && i + 1 != usrs[3])
                        {
                            return i;
                        }
                    }
                }
                // add new user
                if (buttons[buttons.size() - 1].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    if (addUser())
                    {
                        buttons[buttons.size() - 1].setString(users.list[buttons.size() - 1]);
                        tmp.setString("Add new");
                        tmp.move(0, 70);
                        buttons.push_back(tmp);
                    }
                }
                // return
                if (back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    return -1;
                }
            }
        }

        window.clear();
        for (auto btn : buttons)
        {
            window.draw(btn);
        }
        window.draw(back);
        window.display();
    }
}

bool App::addUser()
{
    // string for user name
    sf::String str(L"");

    // texts
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setString("Type your name:");
    title.setPosition(200, 200);

    sf::Text name;
    name.setFont(font);
    name.setCharacterSize(50);
    name.setFillColor(sf::Color::Yellow);
    name.setString(str);
    name.setPosition(200, 300);

    sf::Text confirm;
    confirm.setFont(font);
    confirm.setCharacterSize(50);
    confirm.setFillColor(sf::Color::Yellow);
    confirm.setString("Confirm");
    confirm.setPosition(200, 400);

    sf::Text back;
    back.setFont(font);
    back.setCharacterSize(50);
    back.setFillColor(sf::Color::Yellow);
    back.setString("Back");
    back.setPosition(200, 500);

    // window loop
    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // if string !empty create new user
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter && !str.isEmpty())
            {
                users.list[users.size] = str.toWideString();
                UserData(users.size, users.list[users.size]);
                users.size++;
                return true;
            }
            // return without creating new user
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                return false;
            }
            // enter text
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode >= 32 && event.text.unicode <= 383)
                {
                    str.insert(str.getSize(), static_cast<wchar_t>(event.text.unicode));
                }
                // backspace
                if (event.text.unicode == 8)
                {
                    if (str.getSize() > 0)
                    {
                        str.erase(str.getSize() - 1, 1);
                    }
                }
                name.setString(str);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // if string !empty create new user
                if (confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && !str.isEmpty())
                {
                    users.list[users.size] = str.toWideString();
                    UserData(users.size, users.list[users.size]);
                    users.size++;
                    return true;
                }
                // return without creating new user
                if (back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    return false;
                }
            }
        }

        window.clear();
        window.draw(title);
        window.draw(name);
        window.draw(confirm);
        window.draw(back);
        window.display();
    }
}