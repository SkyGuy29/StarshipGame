#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <math.h>


//effectively just sfml convexShape but my own version instead lol
class Wall 
{
public:
    Wall(std::string);
    int getWallCount() { return point.size(); };
    sf::Vector2f getPoint(int index) { index %= point.getSize(); return point.at(index); };
    void drawTo(sf::RenderWindow& window)
    {
        for (int i = 0; i < point.size(); i++)
        {
            d = point.at(i + 1) - point.at(i);
            double theta;
    
            if (d.x != 0) //preventing division by 0
            {
                theta = atan(d.y / d.x);

                if (d.x < 0) //if its negative...
                    theta += 3.14159; //add pi to get the angles past the range of atan() (> pi/2)
            }
            else if (d.y < 0) //mouse ABOVE player
                theta = -3.14159 / 2;
            else
                theta = 3.14159 / 2;

            
            //setting the line to the two points 
            line.setPosition(point.at(i));
            line.setSize(hypotf(d.x, d.y), 2); //line length equals the distance between points
            line.setRotation(theta * 180 / 3.14159); //convert to degrees and rotates
            window.draw(line);
        }
    }
private:
    std::vector<sf::Vector2f> point;
    sf::RectangleShape line; //draw multiple times
};

/*
walls need:
a series of points
a way to initialize those points from a level file
and a way to collide with player.
*/