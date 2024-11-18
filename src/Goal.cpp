#include "Goal.h"


Goal::Goal()
{
	circ.setRadius(75.f);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	circ.setFillColor(sf::Color::Magenta);
}