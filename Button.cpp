#include "Button.h"


Button::Button()
{
	circ.setRadius(100.f);
	circ.setOrigin(100.f, 100.f);
	circ.setFillColor(sf::Color(0, 175, 175));
	pusab.loadFromFile("pusab.otf");
	text.setFont(pusab);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);
	setString("placeholder");
}


void Button::setPos(sf::Vector2f newPos)
{
	circ.setPosition(newPos);
	text.setPosition(newPos);
}


void Button::setString(std::string newString)
{
	text.setString(newString);	
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(circ.getPosition());
}


bool Button::isActivated(sf::RenderWindow& window)
{
	//if mouse is inside of the circle
	if (distBetween(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))),
		circ.getPosition()) < circ.getRadius())
	{
		circ.setFillColor(sf::Color(0, 210, 210));
		if (!isButtonPressed(sf::Mouse::Left) && mousePressed) //if click just released...
		{
			mousePressed = false;
			return true;
		}
	}
	else
		circ.setFillColor(sf::Color(0, 175, 175));
	
	//checks if the mouse has been pressed, needed for the release check
	if (isButtonPressed(sf::Mouse::Left))
		mousePressed = true;
	else
		mousePressed = false;
	
	return false;
}


void Button::drawTo(sf::RenderWindow& window)
{
	window.draw(circ);
	window.draw(text);
}