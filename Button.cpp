#include "Button.h"


Button::Button(float rad)
{
	clickCirc.setRadius(rad);
	clickCirc.setOrigin(rad, rad);
	clickCirc.setFillColor(sf::Color(0, 200, 200, 200));
	pusab.loadFromFile("pusab.otf");
	text.setFont(pusab);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);
	text.setString("placeholder");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}


void Button::setPos(sf::Vector2f newPos)
{
	clickCirc.setPosition(newPos);
	text.setPosition(newPos);
}


void Button::setString(std::string newString)
{
	text.setString(newString);	
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(clickCirc.getPosition());
}


bool Button::isActivated(sf::RenderWindow& window)
{

	//if mouse is inside of the circle
	if (hypot(sf::Mouse::getPosition(window).y - clickCirc.getPosition().y, sf::Mouse::getPosition(window).x - clickCirc.getPosition().x) < clickCirc.getRadius())
	{
		clickCirc.setFillColor(sf::Color(0, 255, 255, 200));
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed) //if click just released...
		{
			mousePressed = false;
			return true;
		}
	}
	else
		clickCirc.setFillColor(sf::Color(0, 200, 200, 200));
	
	//checks if the mouse has been pressed, needed for the release check
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mousePressed = true;
	
	return false;
}


void Button::drawTo(sf::RenderWindow& window)
{
	window.draw(clickCirc);
	window.draw(text);
}