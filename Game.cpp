#include "Game.h"
#include <iostream>


Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "Shipping People LOL");
    window.setFramerateLimit(FRAMERATE);
    view = window.getDefaultView();
    testButton.setPos(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
    testButton.setString("yay button");
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
            level.update(window, view);
            //pause button and menu
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
        level.update(window, view); //remove this and youll see what it does
        break;
    case Menu::END:
        //load the congratulations text, credits, thanks for playing, and a way to exit
        break;
    default:
        break;
    }
}