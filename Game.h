#pragma once
#include "Level.h"


class Game
{
public:
	Game();
	void run();
private:
	sf::RenderWindow window;
	sf::View view;
};