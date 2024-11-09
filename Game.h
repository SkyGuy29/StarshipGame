#pragma once
#include "Level.h"


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
	sf::RenderWindow window;
	sf::View view;
	Menu currentMenu;
};