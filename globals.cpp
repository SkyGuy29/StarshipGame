#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


static const float PI = 3.14159;
static const int FRAMERATE = 60;


//returns a point based on an easing movement setup, as long as t increases at a constant rate
//t MUST be between 0 and 1.
static sf::Vector2f easeInOut(sf::Vector2f point1, sf::Vector2f point2, float t)
{
    sf::Vector2f d = point1 - point2;
    float ease = t * t * (3.0f - 2.0f * t);

    return sf::Vector2f(d.x * ease, d.y * ease);
}


//returns the distance between the two points.
static float length(sf::Vector2f point1, sf::Vector2f point2)
{
    sf::Vector2f d = point1 - point2;
    return hypotf(d.x, d.y);
}