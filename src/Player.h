#pragma once
#include "Wall.h"
#include "Collectible.h"
#include "Goal.h"


class Player
{
public:
	Player();
	~Player() {};
	//resets player position and enables drawing to window
	void respawn() { circ.setPosition(0, 0); spinner.setPosition(0, 0); slideMode = alive = true; }
	//reactivates player control once the view is done moving
	void ready() { active = true; levelWon = false; }
	//do sprite thing sometime later instead of color (is this even called?)
	void setColor(sf::Color c) { circ.setFillColor(c); spinner.setFillColor(c); } 
	void addVel(sf::Vector2f add) { vel += add; };
	void activateWarp() { warpActive = true; }
	void activateBoost() { slideMode = false; boostTimer.restart(); }
	void kill() { vel.x = vel.y = 0; warpActive = alive = active = false; }
	void win() { vel.x = vel.y = 0; warpActive = active = false; levelWon = true; }
	void setVelAngle(double newAngle) {	angle = newAngle; updateVelocity(); }
	void setVelMagnitude(double newMag) { magnitude = newMag; updateVelocity(); }
	//returns true if player is meant to be shown on screen
	bool isAlive() const { return alive; }
	//returns true if player is meant to be controlled by user
	bool isActive() const { return active; }
	double getVelAngle() const { return angle; };
	double getVelMagnitiude() const { return magnitude; };
	sf::Vector2f getPos() const { return circ.getPosition(); };

	//updates the player based on current states, ex: moving it by its velocity
	void update(sf::RenderWindow&);
	bool isTouching(Wall);
	bool isTouching(Collectible);
	bool isTouching(Goal);
	/*
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
		active = true, //fully interactable
		levelWon = false;
	double angle = 0, magnitude = 0;

	sf::CircleShape circ; //hitbox
	//sprite (doesnt exist yet)
	sf::RectangleShape spinner; //placeholder sprite just to show that aiming works
	sf::Vector2f vel, frictionVel, prevPos;
	sf::Clock boostTimer;
};