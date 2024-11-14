#include "Level.h"


Level::Level()
{

}


void Level::load(int levelNum)
{
	std::fstream file("data.txt", std::ios::in);
	wall.load(file);
	powerups.push_back(Collectible());
	powerups.at(0).load(file);
	file.close();

	bgImg.loadFromFile("the q.jpg");
	background.setTexture(bgImg);
	background.setScale(2, 2);
}


ExitCondition Level::update(sf::RenderWindow& window, sf::View& view)
{
	player.update(window);

	if (player.isTouching(wall))
	{
		player.setColor(sf::Color::Red);
	}
	else
	{
		player.setColor(sf::Color::Cyan);
	}

	if (powerups.size() != 0)
	{
		if (player.isTouching(powerups.at(0)))
		{
			player.activateBoost();
			powerups.pop_back(); //change to an erase
		}
	}

	view.setCenter(player.getPos());

	return ExitCondition::NONE;
}


void Level::drawTo(sf::RenderWindow& window)
{
	window.draw(background);
	wall.drawTo(window);
	for (int i = 0; i < powerups.size(); i++)
	{
		powerups.at(i).drawTo(window);
	}
	player.drawTo(window);
}