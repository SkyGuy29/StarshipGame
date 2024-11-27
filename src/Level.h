#pragma once
#include "Player.h"
#include <string>
#include <fstream>
#include <sstream>


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
	~Level() = default;
	//loads a given level from the id given and the corresponding text file.
	void load(int);
	//handles most of the actual level gameplay, updating all the things going on inside the level
	ExitCondition update(const sf::RenderWindow&, sf::View&);
	//draws all the level's contents to the window
	void drawTo(sf::RenderWindow&);
private:
	bool levelWon = false;

	sf::Texture bgImg;
	sf::Sprite background;
	sf::Clock timer;
	sf::Vector2f viewSlideStart; //used for death reset
	Player player;
	Wall wall; //maybe be a vector later if I need multiple walls like this
	std::vector<Collectible> powerups;
	Goal goal;
};

