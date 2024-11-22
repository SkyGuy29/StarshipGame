#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#define isKeyPressed sf::Keyboard::isKeyPressed
#define isButtonPressed sf::Mouse::isButtonPressed


static const double PI = 3.1415926535897932; //mmm yummy precision
static const int FRAMERATE = 60; //constant for now but will be able to be changed in settings


//returns the position of the mouse relative to the window,
//this is basically a rename since its one line of code lol
static sf::Vector2f mousePos(sf::RenderWindow& window)
{
    return sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}


//returns a point based on an ease in movement setup, as long as t increases at a constant rate
//t MUST be between 0 and 1 for proper easing
static sf::Vector2f easeIn(sf::Vector2f point1, sf::Vector2f point2, float t)
{
    sf::Vector2f d = point2 - point1;
    float ease = t * t;

    return sf::Vector2f(point1.x + d.x * ease, point1.y + d.y * ease);
}


//returns a point based on an ease out movement setup, as long as t increases at a constant rate
//t MUST be between 0 and 1 for proper easing
static sf::Vector2f easeOut(sf::Vector2f point1, sf::Vector2f point2, float t)
{
    sf::Vector2f d = point2 - point1;
    float ease = -t * (t - 2);

    return sf::Vector2f(point1.x + d.x * ease, point1.y + d.y * ease);
}


//returns a point based on an ease in ease out movement setup, as long as t increases at a constant rate
//t MUST be between 0 and 1 for proper easing
static sf::Vector2f easeInOut(sf::Vector2f point1, sf::Vector2f point2, float t)
{
    sf::Vector2f d = point2 - point1;
    float ease = t * t * (3.f - 2.f * t);

    return sf::Vector2f(point1.x + d.x * ease, point1.y + d.y * ease);
}


//returns the distance between the two points.
static float distBetween(sf::Vector2f point1, sf::Vector2f point2)
{
    sf::Vector2f d = point1 - point2;
    return hypotf(d.x, d.y);
}


//returns the angle of the right triangle created by the x and y values of the given points.
static float angleOf(sf::Vector2f p1, sf::Vector2f p2)
{
    sf::Vector2f d = p1 - p2;
    float theta;

    //assigning a value to theta
    if (d.x != 0) //preventing division by 0
    {
        theta = atan(d.y / d.x);

        if (d.x < 0) //if its negative...
            theta += PI; //add pi to get the angles past the range of atan(), angles > pi/2
    }
    else if (d.y < 0) //exactly vertical, p1 above p2
        theta = -PI / 2;
    else //p2 above p1 (iirc LOL)
        theta = PI / 2;

    return theta;
}


//uses the law of cosines to create an angle given the three points.
//the three points are used to create a triangle, and it finds the angle in that triangle
//the angle returned is the one that corresponds to the first parameter/point here.
static float lawOfCos(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
    double a, b, c;
    a = distBetween(p1, p2);
    b = distBetween(p1, p3);
    c = distBetween(p2, p3);

    //the law in states that (the angle opposite of c) = acos((a*a + b*b - c*c) / (2ab))
    return acos((a * a + c * c - b * b) / (2 * a * c));
}


//uses the law of cosines to create an angle in a triangle given its three side lengths.
//the angle returned is the one that is opposite of the last length given here.
static float lawOfCos(float a, float b, float c)
{
    return acos((a * a + c * c - b * b) / (2 * a * c));
}