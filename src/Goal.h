#pragma once
#include "globals.cpp"
#include <fstream>


class Goal
{
public:
	Goal();
	void loadData(float x, float y) { circ.setPosition(sf::Vector2f(x, y)); }
	float getRadius() const { return circ.getRadius(); }
	sf::Vector2f getPos() const { return circ.getPosition(); }
	void drawTo(sf::RenderWindow& window) { window.draw(circ); }
private:
	sf::CircleShape circ;
	//eventually this will have more complex animations but for now yep this is the whole class
};

