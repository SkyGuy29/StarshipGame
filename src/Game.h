#pragma once
#include "Level.h"
#include "Button.h"
#include <deque>


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
	~Game() { delete[] buttons; }
	void run();
private:
	void changeMenu(Menu);

	const int BUTTONS_SIZE = 20;
	int currentLevel = 1;
	bool paused = false, levelComplete = false;

	sf::RenderWindow window;
	sf::View view;
	sf::RectangleShape overlay;
	Level level;
	Button* buttons;
	Menu currentMenu = Menu::START; //do not change without the function
};