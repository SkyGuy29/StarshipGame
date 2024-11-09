#pragma once
#include "Player.h"


enum class ExitCondition
{
	NONE,
	QUIT,
	WIN
};


class Level
{
public:
	Level();
	~Level() {};
	void load(int);
	ExitCondition update();
	void drawTo(sf::RenderWindow&);
private:

};

