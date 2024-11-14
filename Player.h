#pragma once
#include "Wall.h"
#include "Collectible.h"


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
	void setColor(sf::Color c) { hitbox.setFillColor(c); spinner.setFillColor(c); }
	//updates the player based on current states, ex: moving it by its velocity
	void update(sf::RenderWindow&);
	void activateWarp() { warpActive = true; }
	void activateBoost() { slideMode = false; travelTimer.restart(); }
	bool isTouching(Wall);
	bool isTouching(Collectible);
	/*
	bool isTouching(Wormhole);
	bool isTouching(BouncePad);
	bool isTouching(Booster);
	*/
	void drawTo(sf::RenderWindow&);
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