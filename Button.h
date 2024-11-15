#pragma once
#include "globals.cpp"
#include <string>


class Button
{
public:
	Button();
	~Button() {};
	void setRadius(float rad) { clickCirc.setRadius(rad); }
	//changes the current center of the button to a new position
	void setPos(sf::Vector2f);
	//changes the string of the button
	void setString(std::string);
	//returns true if the cursor is on the button and the mouse was just released
	bool isActivated(sf::RenderWindow&);
	//draws the button to a given window
	void drawTo(sf::RenderWindow&);
private:
	bool mousePressed = false;

	sf::CircleShape clickCirc;
	sf::Font pusab;
	sf::Text text; //placeholder until sprites become a thing
};

