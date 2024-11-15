#pragma once
#include "globals.cpp"
#include <fstream>


class Goal
{
public:
	void load(std::fstream&);
	float getRadius() const { return circ.getRadius(); }
	sf::Vector2f getPos() const { return circ.getPosition(); }
	void drawTo(sf::RenderWindow& window) { window.draw(circ); }
private:
	sf::CircleShape circ;
	//eventually this will have more complex animations but for now yep this is the whole class
};

