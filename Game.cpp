#include "Game.h"
#include <iostream>


Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "Shipping People LOL");
    window.setFramerateLimit(FRAMERATE);
    view = window.getDefaultView();
    view.setCenter(0, 0);
    testButton.setPos(sf::Vector2f(0, 0));
    testButton.setString("yay button");
    pauseOverlay.setSize(sf::Vector2f(window.getSize().x - 100, window.getSize().y - 100));
    pauseOverlay.setOrigin(pauseOverlay.getSize() / 2.f);
    pauseOverlay.setFillColor(sf::Color(75, 75, 75, 100));
    pauseButtons[0].setString("Exit");
    pauseButtons[1].setString("Resume");
    pauseButtons[2].setString("Options");
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
            if (testButton.isActivated(window))
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
            if (isKeyPressed(sf::Keyboard::Escape) || isKeyPressed(sf::Keyboard::P))
            {
                paused = true;
                pauseOverlay.setPosition(view.getCenter());
                for (int i = 0; i < 3; i++)
                {
                    pauseButtons[i].setPos(sf::Vector2f(view.getCenter().x + 350 * (i - 1), view.getCenter().y));
                }
            }

            if (!paused)
            {
                level.update(window, view);
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    if (pauseButtons[i].isActivated(window))
                    {
                        paused = false;

                        switch (i)
                        {
                        case 0:
                            changeMenu(Menu::START);
                            break;
                        case 1:
                        case 2:
                            //changeMenu(Menu::SETTINGS) //actually this wouldnt make sense since you are still in level.
                            //we need another overlay
                            break;
                        }
                    }
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
            testButton.drawTo(window);
            break;
        case Menu::SELECT:
            break;
        case Menu::SETTINGS:
            break;
        case Menu::LEVEL:
            level.drawTo(window);
            if (paused)
            {
                window.draw(pauseOverlay);
                for (int i = 0; i < 3; i++)
                {
                    pauseButtons[i].drawTo(window);
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
        level.update(window, view); //remove this and youll see what it does
        break;
    case Menu::END:
        //load the congratulations text, credits, thanks for playing, and a way to exit
        break;
    default:
        break;
    }
}