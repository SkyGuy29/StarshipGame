#include "Wall.h"


Wall::Wall()
{
    line.setSize(sf::Vector2f(20, 2));
    line.setFillColor(sf::Color::White);
    line.setOrigin(0, 1);
}


void Wall::load(std::string fileName)
{
    std::fstream file(fileName, std::ios::in);
    int x, y;

    while (file.is_open() && !file.eof()) //this is somewhat temporary
    {
        file >> x >> y;
        point.push_back(sf::Vector2f(x, y));
    }

    file.close();
}


void Wall::drawTo(sf::RenderWindow& window)
{
    for (int i = 0; i < point.size(); i++)
    {
        sf::Vector2f d = point.at(i + 1) - point.at(i);
        double theta; //yes the whole theta thing is copied from Player::update() read the comments there

        if (d.x != 0)
        {
            theta = atan(d.y / d.x);

            if (d.x < 0)
                theta += 3.14159;
        }
        else if (d.y < 0)
            theta = -3.14159 / 2;
        else
            theta = 3.14159 / 2;


        //setting the line to the two points 
        line.setPosition(point.at(i));
        line.setSize(sf::Vector2f(hypotf(d.x, d.y), 2)); //line length equals the distance between points
        line.setRotation(theta * 180 / 3.14159); //convert to degrees and rotates
        window.draw(line);
    }
}


//this next comment is kept for archive purposes (luna please stop messing with stuff while im not looking)
//hiiiiiii hiiiiiii hiiii :D :D :) :3 :] :} ^-^ =D =) =] =} =3