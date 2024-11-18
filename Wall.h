#pragma once
#include "globals.cpp"
#include <vector>


class Wall 
{
public:
    Wall();
    void loadData(float x, float y) { point.emplace_back(sf::Vector2f(x, y)); }
    int getWallCount() const { return point.size(); };
    sf::Vector2f getPoint(int index) const { index %= point.size(); return point.at(index); };
    void drawTo(sf::RenderWindow&);
private:
    std::vector<sf::Vector2f> point;
    sf::RectangleShape line;
};