#include "Game.h"
#include <iostream>


Game::Game()
{
    buttons = new Button[BUTTONS_SIZE];
    window.create(sf::VideoMode(1280, 720), "Shipping People LOL");
    window.setFramerateLimit(FRAMERATE);
    view = window.getDefaultView();
    view.setCenter(0, 0);
    changeMenu(Menu::START);
    overlay.setSize(sf::Vector2f(window.getSize().x - 100, window.getSize().y - 100));
    overlay.setOrigin(overlay.getSize() / 2.f);
    overlay.setFillColor(sf::Color(75, 75, 75, 100));
}


void Game::run()
{
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        //updates based on the menu
        switch (currentMenu)
        {
        case Menu::START:
            if (buttons[0].isActivated(window))
            {
                changeMenu(Menu::LEVEL); //temporary until level select exists
            }
            break;
        case Menu::SELECT:
            //pressed button will determine currentLevel
            break;
        case Menu::SETTINGS:
            break;
        case Menu::LEVEL:
            //pauses the game
            if (!levelComplete && isKeyPressed(sf::Keyboard::Escape) || isKeyPressed(sf::Keyboard::P))
            {
                paused = true;

                overlay.setPosition(view.getCenter());
                for (int i = 0; i < 3; i++)
                {
                    buttons[i].setPos(sf::Vector2f(view.getCenter().x + 350 * (i - 1), view.getCenter().y));
                    switch (i)
                    {
                    case 0:
                        buttons[i].setString("Exit");
                        break;
                    case 1:
                        buttons[i].setString("Resume");
                        break;
                    case 2:
                        buttons[i].setString("Options");
                        break;
                    }
                }
            }

            //checking pause buttons
            if (paused)
            {
                for (int i = 0; i < BUTTONS_SIZE; i++)
                {
                    if (buttons[i].isActivated(window))
                    {
                        switch (i)
                        {
                        case 0:
                            changeMenu(Menu::START); //break shennanigains lol
                        case 1:
                            paused = false;
                            break;
                        case 2:
                            //changeMenu(Menu::SETTINGS) //actually this wouldnt make sense since you are still in level
                            //we need another overlay
                            break;
                        }
                    }
                }
            }
            //checking level complete buttons
            else if (levelComplete)
            {
                for (int i = 0; i < BUTTONS_SIZE; i++)
                {
                    if (buttons[i].isActivated(window))
                    {
                        levelComplete = false;
                        switch (i)
                        {
                        case 0:
                            //replay level
                            level.load(currentLevel);
                            break;
                        case 1:
                            //next level
                            level.load(++currentLevel);
                            break;
                        case 2:
                            changeMenu(Menu::START);
                            break;
                        }
                    }
                }
            }
            //run the level
            else
            {
                switch (level.update(window, view)) //most game mechanics run in this function
                {
                case ExitCondition::WIN:
                    levelComplete = true;

                    overlay.setPosition(view.getCenter());
                    for (int i = 0; i < 3; i++)
                    {
                        buttons[i].setPos(sf::Vector2f(view.getCenter().x + 350 * (i - 1), view.getCenter().y));
                        switch (i)
                        {
                        case 0:
                            buttons[i].setString("Replay");
                            break;
                        case 1:
                            buttons[i].setString("Next");
                            break;
                        case 2:
                            buttons[i].setString("Menu");
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case Menu::END:
            break;
        default:
            break;
        }

        window.setView(view);

        window.clear();

        //draws based on the menu
        switch (currentMenu)
        {
        case Menu::START:
            buttons[0].drawTo(window);
            break;
        case Menu::SELECT:
            break;
        case Menu::SETTINGS:
            break;
        case Menu::LEVEL:
            level.drawTo(window);
            if (paused || levelComplete)
            {
                window.draw(overlay);
                for (int i = 0 ; i < 3; i++)
                {
                    buttons[i].drawTo(window);
                }
            }
            break;
        case Menu::END:
            break;
        default:
            break;
        }
                
        window.display();
    }
}


void Game::changeMenu(Menu newMenu)
{
    currentMenu = newMenu;

    switch (currentMenu)
    {
    case Menu::START:
        //set button positions
        buttons[0].setString("yay button");
        buttons[0].setPos(sf::Vector2f(0, 0));
        view.setCenter(0, 0);
        break;
    case Menu::SELECT:
        //set all of the level button positions
        break;
    case Menu::SETTINGS:
        //multiple tabs (buttons)
        break;
    case Menu::LEVEL:
        level.load(currentLevel);
        break;
    case Menu::END:
        //load the congratulations text, credits, thanks for playing, and a way to exit
        break;
    default:
        break;
    }
}