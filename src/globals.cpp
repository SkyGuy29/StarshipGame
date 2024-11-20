#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#define isKeyPressed sf::Keyboard::isKeyPressed
#define isButtonPressed sf::Mouse::isButtonPressed


static const float PI = 3.14159;
static const int FRAMERATE = 60;


//returns a point based on an easing movement setup, as long as t increases at a constant rate
//t MUST be between 0 and 1.
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
    else if (d.y < 0) //mouse ABOVE player
        theta = -PI / 2;
    else
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