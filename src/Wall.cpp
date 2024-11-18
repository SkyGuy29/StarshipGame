#include "Wall.h"


Wall::Wall()
{
    line.setSize(sf::Vector2f(20, 4));
    line.setFillColor(sf::Color::White);
    line.setOrigin(0, 2);
}


void Wall::drawTo(sf::RenderWindow& window)
{
    for (int i = 0; i < point.size(); i++)
    {
        double theta = angleOf(getPoint(i + 1), getPoint(i));

        //setting the line to the two points 
        line.setPosition(getPoint(i));
        line.setSize(sf::Vector2f(distBetween(getPoint(i + 1), getPoint(i)), 2));
        line.setRotation(theta * 180 / 3.14159); //convert to degrees and rotates
        window.draw(line);
    }
}


//this next comment is kept for archive purposes (luna please stop messing with stuff while im not looking)
//hiiiiiii hiiiiiii hiiii :D :D :) :3 :] :} ^-^ =D =) =] =} =3