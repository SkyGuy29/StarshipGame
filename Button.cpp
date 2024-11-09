#include "Button.h"


Button::Button(float rad = 100.f)
{
	clickCirc.setRadius(rad);
	clickCirc.setOrigin(rad, rad);
	clickCirc.setFillColor(sf::Color(0, 200, 200, 150));
	pusab.loadFromFile("pusab.otf");
	text.setCharacterSize(20);
	text.setString("placeholder");
	text.setOrigin(text.getGlobalBounds().width, text.getGlobalBounds().height);
}


void Button::setPos(sf::Vector2f newPos)
{
	clickCirc.setPosition(newPos);
	text.setPosition(newPos);
}


void Button::setString(std::string newString)
{
	text.setString(newString);
	text.setOrigin(text.getGlobalBounds().width, text.getGlobalBounds().height);
	text.setPosition(clickCirc.getPosition());
}


bool Button::isActivated(sf::RenderWindow& window)
{
	//if mouse is inside of the circle
	if (hypot(sf::Mouse::getPosition().y - clickCirc.getPosition().y, sf::Mouse::getPosition().x - clickCirc.getPosition().x) < clickCirc.getRadius())
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed) //click just released
			return true;
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		clickCirc.setFillColor(sf::Color(0, 220, 220, 150));
		mousePressed = true;
	}
	else
		clickCirc.setFillColor(sf::Color(0, 200, 200, 150));
	
	return false;
}


void Button::drawTo(sf::RenderWindow& window)
{
	window.draw(clickCirc);
	window.draw(text);
}