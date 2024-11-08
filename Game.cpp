#include "Game.h"
#include <iostream>

Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "Shipping People");
    view = window.getDefaultView();
}

void Game::run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}