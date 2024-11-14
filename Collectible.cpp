#include "Collectible.h"


void Collectible::load(std::fstream& file)
{
	/*
	float x, y;
	file >> id >> x >> y;
	circ.setPosition(x, y);
	*/

	circ.setRadius(10.f);
	circ.setOrigin(10.f, 10.f);
	circ.setPosition(500.f, 400.f);
	circ.setFillColor(sf::Color::Green);
}

//this file is basically pointless ._.