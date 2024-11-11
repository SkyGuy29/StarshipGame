#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>


class Wall 
{
public:
    Wall();
    void load(std::string);
    int getWallCount() const { return point.size(); };
    sf::Vector2f getPoint(int index) const { index %= point.size(); return point.at(index); };
    void drawTo(sf::RenderWindow& window);
private:
    std::vector<sf::Vector2f> point;
    sf::RectangleShape line;
};