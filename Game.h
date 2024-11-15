#pragma once
#include "Level.h"
#include "Button.h"


enum class Menu
{
	START,
	SELECT,
	SETTINGS,
	LEVEL,
	END
};


class Game
{
public:
	Game();
	void run();
private:
	void changeMenu(Menu);

	int currentLevel = 1;
	bool paused = false;

	sf::RenderWindow window;
	sf::View view;
	sf::RectangleShape pauseOverlay;
	Level level;
	Button testButton, pauseButtons[3]; //needs to be a vector eventually
	Menu currentMenu = Menu::START; //do not change without the function
};