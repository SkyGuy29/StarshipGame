#include "Game.h"
#include "Level.h"
#include "Button.h"
#include <iostream>


Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "Shipping People LOL");
    window.setFramerateLimit(60);
    view = window.getDefaultView();
    testButton.setPos(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    testButton.setString("yay button");
}


void Game::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //updates based on the menu
        switch (currentMenu)
        {
        case Menu::START:
            if (testButton.isActivated(window))
            {
                changeMenu(Menu::LEVEL);
            }
            break;
        case Menu::SELECT:
            //pressed button will determine currentLevel
            break;
        case Menu::SETTINGS:
            break;
        case Menu::LEVEL:
            level.update();
            //pause button and menu
            break;
        case Menu::END:
            break;
        default:
            break;
        }
        

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