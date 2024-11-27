#pragma once
#include "globals.hpp"
#include <fstream>


class Goal
{
public:
	Goal();
	void loadData(const float x, const float y) { circ.setPosition(sf::Vector2f(x, y)); }
	float getRadius() const { return circ.getRadius(); }
	sf::Vector2f getPos() const { return circ.getPosition(); }
	void drawTo(sf::RenderWindow& window) const { window.draw(circ); }
private:
	sf::CircleShape circ;
	//eventually this will have more complex animations but for now yep this is the whole class
};

