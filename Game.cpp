#include "Game.h"
#include "Button.h"
#include <iostream>


Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "Shipping People LOL");
    view = window.getDefaultView();
}


void Game::run()
{
    Button testButton;
    
    testButton.setPos(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    testButton.setString("yay button");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (testButton.isActivated(window))
        {
            std::cout << "yay\n";
        }

        window.clear();
        testButton.drawTo(window);
        window.display();
    }
}