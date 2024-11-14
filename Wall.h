#pragma once
#include "globals.cpp"
#include <vector>
#include <string>
#include <math.h>
#include <fstream>


class Wall 
{
public:
    Wall();
    void load(std::fstream&);
    int getWallCount() const { return point.size(); };
    sf::Vector2f getPoint(int index) const { index %= point.size(); return point.at(index); };
    void drawTo(sf::RenderWindow&);
private:
    std::vector<sf::Vector2f> point;
    sf::RectangleShape line;
};