#include "Level.h"


Level::Level()
{

}


void Level::load(int levelNum)
{
	bgImg.loadFromFile("the q.jpg");
	background.setTexture(bgImg);
}


ExitCondition Level::update(sf::RenderWindow& window, sf::View& view)
{
	player.update(window);
	view.setCenter(player.getPos());

	return ExitCondition::NONE;
}


void Level::drawTo(sf::RenderWindow& window, bool showHitboxes)
{
	window.draw(background);
	player.drawTo(window, showHitboxes);
}