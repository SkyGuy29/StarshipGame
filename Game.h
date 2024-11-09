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
	Level level;
	sf::RenderWindow window;
	sf::View view;
	Menu currentMenu = Menu::START; //do not change without the function
	int currentLevel = 1;

	Button testButton; //needs to be a vector eventually
};