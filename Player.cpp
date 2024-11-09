#include "Player.h"


Player::Player()
{
	hitbox.setFillColor(sf::Color::Cyan);
	hitbox.setRadius(30.f);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
}


void Player::setVelAngle(double newAngle)
{
	angle = newAngle;
	updateVelocity();
}


void Player::setVelMagnitude(double newMagnitude)
{
	magnitude = newMagnitude;
	updateVelocity();
}


void Player::update()
{
	//spin function
}


void Player::drawTo(sf::RenderWindow& window, bool showHitboxes)
{
	window.draw(spinner);
	window.draw(hitbox);
}


void Player::updateVelocity()
{
	vel.x = magnitude * cos(angle); //negative?
	vel.y = magnitude * sin(angle);
}
