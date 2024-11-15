#include "Goal.h"


void Goal::load(std::fstream& file)
{
	/*
	float x, y;
	file >> x >> y;
	circ.setPosition(x, y);
	*/

	circ.setRadius(75.f);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	circ.setFillColor(sf::Color::Magenta);
	circ.setPosition(700.f, 700.f);
}