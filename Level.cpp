#include "Level.h"


Level::Level()
{

}


void Level::load(int levelNum)
{
	bgImg.loadFromFile("the q.jpg");
	wall.load("walls.txt");
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
	view.setCenter(player.getPos());

	return ExitCondition::NONE;
}


void Level::drawTo(sf::RenderWindow& window, bool showHitboxes)
{
	window.draw(background);
	wall.drawTo(window);
	player.drawTo(window, showHitboxes);
}