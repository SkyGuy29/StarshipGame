#pragma once
#include "globals.hpp"
#include <fstream>


enum ID
{
	BOOST = 0,
	WARP = 1,
	TOGGLE = 2,
	SECRET = 3
};
//ids exactly correspond to ids in data files


class Collectible
{
public:
	Collectible();
	void loadData(const float x, const float y, const int newID) { circ.setPosition(sf::Vector2f(x, y)); id = newID; }
	float getRadius() const { return circ.getRadius(); }
	sf::Vector2f getPos() const { return circ.getPosition(); }
	int getID() const { return id; }
	void drawTo(sf::RenderWindow& window) const { window.draw(circ); }
private:
	int id = ID::BOOST; //determines what collectible does
	sf::CircleShape circ;
};

