#include "Collectible.h"


void Collectible::load(std::fstream& file)
{
	/*
	float x, y;
	file >> id >> x >> y;
	circ.setPosition(x, y);
	*/

	circ.setRadius(20.f);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	circ.setPosition(500.f, 400.f);
	circ.setFillColor(sf::Color::Green);
}

//this file is basically pointless ._.