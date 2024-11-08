#pragma once
#include <SFML/Graphics.hpp>


class Player
{
public:
	Player();
	double getVelAngle() const;
	double getVelMagnitiude() const;
	void setVelAngle(double);
	void setVelMagnitude(double);
	void update();
	sf::Vector2f getPos();
	void drawTo(sf::RenderWindow&, bool);
private:
	void updateVelocity();
	double angle, magnitude;
	//hitbox
	sf::CircleShape hitbox;
	//sprite
	sf::ConvexShape triangle; //placeholder sprite
	sf::Vector2f vel;

};

