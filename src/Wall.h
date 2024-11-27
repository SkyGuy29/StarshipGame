#pragma once
#include "globals.hpp"
#include <vector>


class Wall 
{
public:
    Wall();
    void loadData(float x, float y) { point.emplace_back(x, y); }
    void resetData() { point.clear(); }
    int getWallCount() const { return point.size(); }
    sf::Vector2f getPoint(int index) const { index %= point.size(); return point.at(index); }
    void drawTo(sf::RenderWindow&);
private:
    std::vector<sf::Vector2f> point;
    sf::RectangleShape line;
};