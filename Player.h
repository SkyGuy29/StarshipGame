#pragma once
#include "Wall.h"
#include "Collectible.h"


class Player
{
public:
	Player();
	~Player() {};
	double getVelAngle() const { return angle; };
	double getVelMagnitiude() const { return magnitude; };
	sf::Vector2f getPos() const { return hitbox.getPosition(); };
	//resets player position and enables drawing to window
	void respawn() { hitbox.setPosition(0, 0); spinner.setPosition(0, 0); slideMode = alive = true; }
	//reacivates player control once the view is done moving
	void ready() { active = true; }
	void addVel(sf::Vector2f add) { vel += add; };
	void setVelAngle(double);
	void setVelMagnitude(double);
	void setColor(sf::Color c) { hitbox.setFillColor(c); spinner.setFillColor(c); }
	//updates the player based on current states, ex: moving it by its velocity
	void update(sf::RenderWindow&);
	void activateWarp() { warpActive = true; }
	void activateBoost() { slideMode = false; travelTimer.restart(); }
	void kill() { vel.x = vel.y = 0; warpActive = alive = active = false; }
	bool isAlive() const { return alive; }
	bool isActive() const { return active; }
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
	//updates velocity based on angle and/or magnitude changes
	void updateVelocity();

	bool mousePressed = false, warpActive = false, slideMode = true, 
		alive = true, //visible, may not be interactable
		active = true; //fully interactable. difference is due to respawning
	double angle = 0, magnitude = 0;

	//hitbox
	sf::CircleShape hitbox;
	//sprite
	sf::RectangleShape spinner; //placeholder sprite just to show that aiming works
	sf::Vector2f vel, initVel;
	sf::Clock travelTimer;
};