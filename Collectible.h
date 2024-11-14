#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

class Collectible
{
public:

	void load(std::fstream&);
	float getRadius() const { return circ.getRadius(); }
	sf::Vector2f getPos() const { return circ.getPosition(); }
	int getID() const { return id; }
	void drawTo(sf::RenderWindow& window) { window.draw(circ); }
private:
	int id = 0; //determines what colectible does, may enumerate
	sf::CircleShape circ;
};

/*
types of collectibles:
gives player a one use warp
gives player a boost (travel mode or whatever)
toggles off a lazer that blocks path?
secret collectible
*/

