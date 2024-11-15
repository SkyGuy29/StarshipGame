#pragma once
#include "globals.cpp"
#include <fstream>


enum ID
{
	BOOST,
	WARP,
	TOGGLE,
	SECRET
};


class Collectible
{
public:
	void load(std::fstream&);
	float getRadius() const { return circ.getRadius(); }
	sf::Vector2f getPos() const { return circ.getPosition(); }
	int getID() const { return id; }
	void setID(int newID) { id = newID; } //THIS IS TEMPORARY ID WILL BE DETERMINED ON LOAD ONLY IN FINAL
	void drawTo(sf::RenderWindow& window) { window.draw(circ); }
private:
	int id = ID::BOOST; //determines what colectible does, may enumerate
	sf::CircleShape circ;
};

