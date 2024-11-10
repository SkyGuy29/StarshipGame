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

	Level level;
	sf::RenderWindow window;
	sf::View view;
	Menu currentMenu = Menu::START; //do not change without the function
	Button testButton; //needs to be a vector eventually
};