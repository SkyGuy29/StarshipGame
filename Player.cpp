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

    sf::Vector2f mouseMap(window.mapPixelToCoords(sf::Mouse::getPosition(window))), d;

    d.x = mouseMap.x - hitbox.getPosition().x;
    d.y = mouseMap.y - hitbox.getPosition().y;

    if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        float negative = 1; //needs to be a float in case of rounding issues
        double theta;


        //std::cout << d.x << std::endl;

        if (d.x != 0) //preventing division by 0
        {
            theta = atan(d.y / d.x);
            negative = d.x / abs(d.x); //should be just 1 or -1
        }
        else if (d.y < 0) //mouse ABOVE player
            theta = -3.14159 / 2;
        else
            theta = 3.14159 / 2;

        vel.x = 10 * cos(theta) * negative; //10 is speed, make this a constant later
        vel.y = 10 * sin(theta) * negative;

        hitbox.setPosition(hitbox.getPosition() + vel);
    }

    if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        vel.x = d.x / ((FRAMERATE + 1) / 2.f); //okay i dont like magic code but i actually do not know the explanation
        vel.y = d.y / ((FRAMERATE + 1) / 2.f);

        initVel = vel;
        //glock.restart();
        mousePressed = true;
    }

    if (mousePressed)
    {
        if (abs(vel.x) >= abs(initVel.x) / FRAMERATE && abs(vel.y) >= abs(initVel.y) / FRAMERATE)
        {
            hitbox.setPosition(hitbox.getPosition() + vel);
            vel.x -= initVel.x / FRAMERATE; //should take exactly one second to slide
            vel.y -= initVel.y / FRAMERATE;


        }
        else
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                mousePressed = false;
            vel.x = vel.y = 0;
            //std::cout << glock.getElapsedTime().asMilliseconds() << std::endl;
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
    sf::CircleShape player(20.f), cursorCirc(10.f);
    sf::Vector2f vel, initVel;
    sf::View view(window.getView());
    sf::Texture image;
    sf::Sprite background;
    //sf::Clock glock;

    MovementMode moveMode = MovementMode::SLIDE;

    bool mousePressed = false;
    float fadeCounter = 255;

    image.loadFromFile("the q.jpg");
    background.setTexture(image);
    background.setScale(5, 5);

    player.setFillColor(sf::Color::Cyan);
    player.setOrigin(player.getRadius(), player.getRadius());
    player.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    cursorCirc.setOrigin(cursorCirc.getRadius(), cursorCirc.getRadius());
    cursorCirc.setPosition(player.getPosition());
    cursorCirc.setFillColor(sf::Color::Transparent);
    window.setFramerateLimit(FRAMERATE);

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f mouseMap(window.mapPixelToCoords(sf::Mouse::getPosition(window))), d;

        d.x = mouseMap.x - player.getPosition().x;
        d.y = mouseMap.y - player.getPosition().y;

        if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            float negative = 1; //needs to be a float in case of rounding issues
            double theta;


            //std::cout << d.x << std::endl;

            if (d.x != 0) //preventing division by 0
            {
                theta = atan(d.y / d.x);
                negative = d.x / abs(d.x); //should be just 1 or -1
            }
            else if (d.y < 0) //mouse ABOVE player
                theta = -3.14159 / 2;
            else
                theta = 3.14159 / 2;

            vel.x = 10 * cos(theta) * negative; //10 is speed, make this a constant later
            vel.y = 10 * sin(theta) * negative;

            player.setPosition(player.getPosition() + vel);
            view.setCenter(player.getPosition());
        }

        if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            vel.x = d.x / ((FRAMERATE + 1) / 2.f); //okay i dont like magic code but i actually do not know the explanation
            vel.y = d.y / ((FRAMERATE + 1) / 2.f);

            initVel = vel;
            cursorCirc.setPosition(mouseMap);
            fadeCounter = 255;
            //glock.restart();
            mousePressed = true;
        }

        if (mousePressed)
        {
            if (abs(vel.x) >= abs(initVel.x) / FRAMERATE && abs(vel.y) >= abs(initVel.y) / FRAMERATE)
            {
                player.setPosition(player.getPosition() + vel);
                view.setCenter(player.getPosition());
                vel.x -= initVel.x / FRAMERATE; //should take exactly one second to slide
                vel.y -= initVel.y / FRAMERATE;

                cursorCirc.setFillColor(sf::Color(255, 0, 0, fadeCounter));

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
                //std::cout << glock.getElapsedTime().asMilliseconds() << std::endl;
            }
        }

        window.setView(view);

        window.clear();
        window.draw(background);
        window.draw(player);
        window.draw(cursorCirc);
        window.display();
    }

    return 0;
*/