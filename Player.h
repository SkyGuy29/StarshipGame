#pragma once
#include <SFML/Graphics.hpp>


class Player
{
public:
	Player();
	~Player() {};
	double getVelAngle() const { return angle; };
	double getVelMagnitiude() const { return magnitude; };
	sf::Vector2f getPos() const { return hitbox.getPosition(); };
	void setVelAngle(double);
	void setVelMagnitude(double);
	void update(sf::RenderWindow&);
	void drawTo(sf::RenderWindow&, bool = false);
private:
	void updateVelocity();
	double angle = 0, magnitude = 0;
	//hitbox
	sf::CircleShape hitbox;
	//sprite
	sf::RectangleShape spinner; //placeholder sprite just to show that aiming works
	sf::Vector2f vel, initVel;
	bool mousePressed;
};