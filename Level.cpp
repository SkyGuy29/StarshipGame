#include "Level.h"


Level::Level()
{

}


void Level::load(int levelNum)
{
	bgImg.loadFromFile("the q.jpg");
	wall.load("walls.txt");
	background.setTexture(bgImg);
}


ExitCondition Level::update(sf::RenderWindow& window, sf::View& view)
{
	player.update(window);
	if (player.isTouching(wall))
	{
		std::cout << "hi";
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