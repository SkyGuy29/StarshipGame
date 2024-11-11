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
	//loads a given level from the id given and the corresponding text file.
	void load(int);
	//handles most of the actual level gameplay, updating all of the things going on inside of the level
	ExitCondition update(sf::RenderWindow&, sf::View&);
	//draws all of the level's contents to the window
	void drawTo(sf::RenderWindow&, bool = false);
private:
	sf::Texture bgImg;
	sf::Sprite background;
	Player player;
	Wall wall; //should be vector later
};

