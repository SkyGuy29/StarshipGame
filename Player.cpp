#include "Player.h"

Player::Player()
{
}


double Player::getVelAngle() const
{
	return 0.0;
}


double Player::getVelMagnitiude() const
{
	return 0.0;
}


void Player::setVelAngle(double newAngle)
{

}


void Player::setVelMagnitude(double newMagnitude)
{
	
}


void Player::update()
{
	//spin function
}


sf::Vector2f Player::getPos()
{
	return sf::Vector2f();
}


void Player::drawTo(sf::RenderWindow& window, bool showHitboxes)
{

}

void Player::updateVelocity()
{
	vel.x = magnitude * cos(angle); //negative?
	vel.y = magnitude * sin(angle);
}
