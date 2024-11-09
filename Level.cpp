#include "Level.h"


Level::Level()
{

}


void Level::load(int levelNum)
{
	bgImg.loadFromFile("the q.jpg");
	background.setTexture(bgImg);
}


ExitCondition Level::update()
{
	player.update();

	return ExitCondition::NONE;
}


void Level::drawTo(sf::RenderWindow& window, bool showHitboxes)
{
	window.draw(background);
	player.drawTo(window, showHitboxes);
}