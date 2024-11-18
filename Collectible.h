#pragma once
#include "globals.cpp"
#include <fstream>


enum ID
{
	BOOST = 0,
	WARP = 1,
	TOGGLE = 2,
	SECRET = 3
};
//ids exactly coorespond to ids in data files


class Collectible
{
public:
	Collectible();
	void loadData(float x, float y, int newID) { circ.setPosition(sf::Vector2f(x, y)); id = newID; }
	float getRadius() const { return circ.getRadius(); }
	sf::Vector2f getPos() const { return circ.getPosition(); }
	int getID() const { return id; }
	void drawTo(sf::RenderWindow& window) { window.draw(circ); }
private:
	int id = ID::BOOST; //determines what colectible does
	sf::CircleShape circ;
};

