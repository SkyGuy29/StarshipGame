#include <SFML/Graphics.hpp>
#include <iostream>


const float PI = 3.14159;
const int FRAMERATE = 60;


static float easeInOut(float t)
{
    return t * t * (3.0f - 2.0f * t);
}


static float length(sf::Vector2f point1, sf::Vector2f point2)
{
    sf::Vector2f d = point1 - point2;
    return hypotf(d.x, d.y);
}