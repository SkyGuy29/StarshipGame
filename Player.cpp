#include "Player.h"


Player::Player()
{
	hitbox.setFillColor(sf::Color::Cyan);
	hitbox.setRadius(30.f);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
    spinner.setSize(sf::Vector2f(50, 16));
    spinner.setFillColor(sf::Color::Cyan);
    spinner.setOrigin(0, 8);
}


void Player::update(sf::RenderWindow& window)
{
    sf::Vector2f mouseMap(window.mapPixelToCoords(sf::Mouse::getPosition(window))), 
        d = mouseMap - hitbox.getPosition();

    
    double theta; //angle between mouse and player, different than the angle member which is used for velocity

    //assigning a value to theta
    if (d.x != 0) //preventing division by 0
    {
        theta = atan(d.y / d.x);

        if (d.x < 0) //if its negative...
            theta += 3.14159; //add pi to get the angles past the range of atan(), angles > pi/2
    }
    else if (d.y < 0) //mouse ABOVE player
        theta = -3.14159 / 2;
    else
        theta = 3.14159 / 2;

    //aims the spinner at the cursor using math
    spinner.setRotation(theta * 180 / 3.14159); //convert to degrees lol

    //debug keys, will be removed when colectibles are added
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        slideMode = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        slideMode = false;
        travelTimer.restart();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        warpActive = true;
    }

    //changes movement based on the current mode
    if (slideMode)
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed)
        {
            if (warpActive)
            {
                hitbox.setPosition(mouseMap);
                //instantly warp player and have view catch up (fast, slide math for easing????????)
                warpActive = false;
            }
            else
            {
                vel.x = d.x / ((FRAMERATE + 1) / 2.f); //okay i dont like magic code but i actually do not know the explanation
                vel.y = d.y / ((FRAMERATE + 1) / 2.f); //also this is the only case where it makes more sense to directly set vel than use angle and magnitude
                initVel = vel;
            }
        }
    }
    else
    {
        angle = theta; //will now move player toward the mouse
        magnitude = 10; //at a constant speed
        updateVelocity();

        if (warpActive && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed)
        {
            hitbox.setPosition(mouseMap);
            //instantly warp player and have view catch up (fast, slide math for easing????????)
            warpActive = false;
        }

        if (travelTimer.getElapsedTime().asMilliseconds() >= 2000)
        {
            slideMode = true;
        }
    }

    //moves the player if it has velocity
    if (vel.x != 0 && vel.y != 0)
    {
        hitbox.setPosition(hitbox.getPosition() + vel);
        if (slideMode)
            decelerate();
    }

    spinner.setPosition(hitbox.getPosition());

    //used for checking when a release has happened
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mousePressed = true;
    else
        mousePressed = false;
}


bool Player::isTouching(Wall wall)
{
    double a, b, c, beta, gamma, const PI = 3.14159;

    for (int i = 0; i < wall.getWallCount(); i++)
    {
        a = length(wall.getPoint(i), wall.getPoint(i + 1));
        b = length(hitbox.getPosition(), wall.getPoint(i));
        c = length(hitbox.getPosition(), wall.getPoint(i + 1));

        /* law of cosines to find angle
        the law in question: angle = acos((a*a + b*b - c*c) / (2ab))
        compare distance to readius of the circle */
        beta = acos((a * a + c * c - b * b) / (2 * a * c));
        gamma = acos((a * a + b * b - c * c) / (2 * a * b));

        if ((b < hitbox.getRadius() || c < hitbox.getRadius())
            || (gamma <= PI / 2.f && beta <= PI / 2.f 
            && b * sin(gamma) < hitbox.getRadius()))
        {
            return true;
        }
    }

    return false;
}


bool Player::isTouching(Collectible collect)
{
    //gotta love how comically easy this is compared to the wall collision
    return length(collect.getPos(), getPos()) <= hitbox.getRadius() + collect.getRadius();
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


void Player::drawTo(sf::RenderWindow& window)
{
	window.draw(spinner);
	window.draw(hitbox);
}


void Player::decelerate()
{
    //if the next velocity change would result in it flipping signs, that means it is done running and should be set to 0
    if (abs(vel.x) >= abs(initVel.x) / FRAMERATE && abs(vel.y) >= abs(initVel.y) / FRAMERATE)
    {
        vel.x -= initVel.x / FRAMERATE; //should take exactly one second to slide
        vel.y -= initVel.y / FRAMERATE;
    }
    else
        vel.x = vel.y = 0;
}


void Player::updateVelocity()
{
	vel.x = magnitude * cos(angle);
	vel.y = magnitude * sin(angle);
    initVel = vel;
}