#include "Player.h"


Player::Player()
{
	hitbox.setFillColor(sf::Color::Cyan);
	hitbox.setRadius(30.f);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
}


void Player::setVelAngle(double newAngle)
{
	angle = newAngle;
	updateVelocity();
}


void Player::setVelMagnitude(double newMagnitude)
{
	magnitude = newMagnitude;
	updateVelocity();
}


void Player::update(sf::RenderWindow& window)
{
	//spin function

    const int FRAMERATE = 60;

    sf::Vector2f mouseMap(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

    if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        float negative = 1;
        double theta;
        sf::Vector2f d;

        d.x = mouseMap.x - hitbox.getPosition().x;
        d.y = mouseMap.y - hitbox.getPosition().y;

        //std::cout << d.x << std::endl;

        if (abs(d.x) >= 0.00001) //preventing division by 0
        {
            theta = atan(d.y / d.x);
            negative = (d.x) / abs(d.x);
        }
        else if (d.y < 0)
            theta = -3.14159 / 2;
        else
            theta = 3.14159 / 2;

        vel.x = 10 * cos(theta) * negative;
        vel.y = 10 * sin(theta) * negative;

        hitbox.setPosition(hitbox.getPosition() + vel);
    }

    if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        vel.x = (mouseMap.x - hitbox.getPosition().x) / ((FRAMERATE + 1) / 2.f); //okay i dont like magic code but i actually do not know the explanation
        vel.y = (mouseMap.y - hitbox.getPosition().y) / ((FRAMERATE + 1) / 2.f);

        initVel = vel;
        mousePressed = true;
    }

    if (mousePressed)
    {
        if (abs(vel.x) >= abs(initVel.x) / FRAMERATE && abs(vel.y) >= abs(initVel.y) / FRAMERATE)
        {
            hitbox.setPosition(hitbox.getPosition() + vel);
            vel.x -= initVel.x / FRAMERATE; //should take exactly one second
            vel.y -= initVel.y / FRAMERATE;
        }
        else
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                mousePressed = false;
            vel.x = vel.y = 0;
        }
    }
}


void Player::drawTo(sf::RenderWindow& window, bool showHitboxes)
{
	window.draw(spinner);
	window.draw(hitbox);
}


void Player::updateVelocity()
{
	vel.x = magnitude * cos(angle); //negative?
	vel.y = magnitude * sin(angle);
}







/*
sf::RenderWindow window(sf::VideoMode(1280, 720), "Starship game thingy perchance lol");
    sf::CircleShape shape(20.f), mousePos(10.f);
    sf::Vector2f vel, initVel;
    sf::View view(window.getView());
    sf::Texture image;
    sf::Sprite sprite;
    sf::Clock glock;

    MovementMode moveMode = MovementMode::SLIDE;

    bool mousePressed = false;
    float fadeCounter = 255;

    image.loadFromFile("the q.jpg");
    sprite.setTexture(image);
    sprite.setScale(5, 5);

    shape.setFillColor(sf::Color::Cyan);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    mousePos.setOrigin(mousePos.getRadius(), mousePos.getRadius());
    mousePos.setPosition(shape.getPosition());
    mousePos.setFillColor(sf::Color::Transparent);
    window.setFramerateLimit(FRAMERATE);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f mouseMap(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

        if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            float negative = 1;
            double theta;
            sf::Vector2f d;

            d.x = mouseMap.x - shape.getPosition().x;
            d.y = mouseMap.y - shape.getPosition().y;

            //std::cout << d.x << std::endl;

            if (abs(d.x) >= 0.00001) //preventing division by 0
            {
                theta = atan(d.y / d.x);
                negative = (d.x) / abs(d.x);
            }
            else if (d.y < 0)
                theta = -3.14159 / 2; //we love radians!!
            else
                theta = 3.14159 / 2;

            vel.x = 10 * cos(theta) * negative;
            vel.y = 10 * sin(theta) * negative;

            shape.setPosition(shape.getPosition() + vel);
            view.setCenter(shape.getPosition());
        }

        if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            vel.x = (mouseMap.x - shape.getPosition().x) / ((FRAMERATE + 1) / 2.f); //okay i dont like magic code but i actually do not know the explanation
            vel.y = (mouseMap.y - shape.getPosition().y) / ((FRAMERATE + 1) / 2.f);

            initVel = vel;
            mousePos.setPosition(mouseMap);
            fadeCounter = 255;
            glock.restart();
            mousePressed = true;
        }

        if (mousePressed)
        {
            if (abs(vel.x) >= abs(initVel.x) / FRAMERATE && abs(vel.y) >= abs(initVel.y) / FRAMERATE)
            {
                shape.setPosition(shape.getPosition() + vel);
                view.setCenter(shape.getPosition());
                vel.x -= initVel.x / FRAMERATE; //should take exactly one second
                vel.y -= initVel.y / FRAMERATE;

                mousePos.setFillColor(sf::Color(255, 0, 0, fadeCounter));

                if (fadeCounter > 0)
                    fadeCounter -= 255.f / FRAMERATE * 4;
                else
                    fadeCounter = 0;
            }
            else
            {
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    mousePressed = false;
                vel.x = vel.y = 0;
                std::cout << glock.getElapsedTime().asMilliseconds() << std::endl;
            }
        }

        window.setView(view);

        window.clear();
        window.draw(sprite);
        window.draw(shape);
        window.draw(mousePos);
        window.display();
    }

    return 0;
*/