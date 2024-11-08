#pragma once
#include <SFML/Graphics.hpp>


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
	void load();
	ExitCondition update();
private:

};

