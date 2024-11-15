#include "Level.h"


Level::Level()
{
	bgImg.loadFromFile("the q.jpg");
	background.setTexture(bgImg);
	background.setScale(2, 2);
}


void Level::load(int levelNum)
{
	std::fstream file("data.txt", std::ios::in);
	wall.load(file);
	for (int i = 0; i < 4; i++)
	{
		powerups.push_back(Collectible());
		powerups.at(i).load(file);
		powerups.at(i).setID(i);
	}
	file.close();
}


ExitCondition Level::update(sf::RenderWindow& window, sf::View& view)
{
	player.update(window);

	if (player.isActive())
	{
		if (player.isTouching(wall))
		{
			player.kill();
			timer.restart();
		}

		for (int i = 0; i < powerups.size(); i++)
		{
			if (player.isTouching(powerups.at(i)))
			{
				switch (powerups.at(i).getID())
				{
				case ID::BOOST:
					player.activateBoost();
					break;
				case ID::WARP:
					player.activateWarp();
					break;
				case ID::TOGGLE:
					std::cout << "lol\n";
					break;
				case ID::SECRET:
					std::cout << "YAAAAAAAAAAAAAAGH\n";
					break;
				default:
					break;
				}

				player.activateBoost();
				powerups.erase(powerups.begin() + i);
			}
		}

		view.setCenter(player.getPos());
	}
	else if (timer.getElapsedTime().asMilliseconds() >= 1500)
	{
		if (!player.isAlive())
		{
			viewSlideStart = player.getPos();
			player.respawn();
		}

		if(timer.getElapsedTime().asMilliseconds() < 2000)
		{
			view.setCenter(easeInOut(viewSlideStart, player.getPos(),
				(timer.getElapsedTime().asMilliseconds() - 1500) / 500.f));
		}
		else
		{
			player.ready();
		}
	}


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