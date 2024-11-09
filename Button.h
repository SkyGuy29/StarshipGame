#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class Button
{
public:
	Button(float = 100.f);
	~Button() {};
	//changes the current center of the button to a new position
	void setPos(sf::Vector2f);
	//changes the string of the button
	void setString(std::string);
	//returns true if the cursor is on the button and the mouse was just released
	bool isActivated(sf::RenderWindow&);
	//draws the button to a given window
	void drawTo(sf::RenderWindow&);
private:
	sf::CircleShape clickCirc;
	sf::Font pusab;
	sf::Text text; //placeholder until sprites become a thing
	bool mousePressed = false;
};

