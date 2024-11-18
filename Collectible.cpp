#include "Collectible.h"


Collectible::Collectible()
{
	circ.setRadius(20.f);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	circ.setFillColor(sf::Color::Green);
}

//this file is basically pointless ._.