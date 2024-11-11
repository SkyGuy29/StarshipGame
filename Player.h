#pragma once
#include "Wall.h"


const int FRAMERATE = 60;


class Player
{
public:
	Player();
	~Player() {};
	double getVelAngle() const { return angle; };
	double getVelMagnitiude() const { return magnitude; };
	sf::Vector2f getPos() const { return hitbox.getPosition(); };
	void addVel(sf::Vector2f add) { vel += add; };
	void setVelAngle(double);
	void setVelMagnitude(double);
	void update(sf::RenderWindow&);
	bool isTouching(Wall);
	/*
	bool isTouching(Wormhole);
	bool isTouching(Collectible));
	bool isTouching(BouncePad);
	bool isTouching(Booster);
	*/
	void drawTo(sf::RenderWindow&, bool = false);
private:
	void decelerate();
	void updateVelocity();
	float length(sf::Vector2f, sf::Vector2f);

	bool mousePressed = false, warpActive = false, slideMode = true;
	double angle = 0, magnitude = 0;

	//hitbox
	sf::CircleShape hitbox;
	//sprite
	sf::RectangleShape spinner; //placeholder sprite just to show that aiming works
	sf::Vector2f vel, initVel;
	sf::Clock travelTimer;
};