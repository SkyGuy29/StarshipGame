#include "Level.h"
#include <vector>


Level::Level()
{
	bgImg.loadFromFile("the q.jpg");
	background.setTexture(bgImg);
	background.setScale(2, 2);
}


void Level::load(int levelNum)
{
	std::ifstream file("data.txt"); //make this use levelNum pls =] yes you will need new files also organize
    std::string line;
	char currentLoad = ' ';

    if (!file)
    {
        std::cerr << "Unable to open file.\n";
    }

    //Read the file line by line
    while (file.is_open() && std::getline(file, line))
    {
        if (!line.empty() && line[0] == '(') 
        {
			currentLoad = line[1];
        }
		else if (line[0] != '/') //skips any comments like this one! no multilines tho...
		{
			std::istringstream iss(line); //chatgpt gave me this in full honesty, works for getting my data from the line tho
			float x, y, id;

			switch (currentLoad) //this in theory should let you swap them around and it will still work
			{
			case 'w':
			case 'W':
				iss >> x >> y;
				wall.loadData(x, y);
				break;
			case 'c':
			case 'C':
				iss >> x >> y >> id;
				powerups.emplace_back();
				powerups.at(powerups.size() - 1).loadData(x, y, id);
				break;
			case 'g':
			case 'G':
				iss >> x >> y;
				goal.loadData(x, y);
				break;
			deafult:
				std::cout << currentLoad << " << this character, loaded from your file, does not coorespond to a level element.\n";
			}
		}
    }

    file.close();
}


ExitCondition Level::update(sf::RenderWindow& window, sf::View& view)
{
	//updating player stuff (like moving) before checking collisions
	player.update(window);

	if (player.isActive())
	{
		if (player.isTouching(wall))
		{
			player.kill();
			timer.restart(); //animation timer
		}

		if (player.isTouching(goal))
		{
			levelWon = true;
			player.win();
			viewSlideStart = player.getPos(); //for animation
			timer.restart(); //animation timer
		}

		//checking powerups collision
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
					std::cout << "lol\n"; //placeholder ofc
					break;
				case ID::SECRET:
					std::cout << "YAAAAAAAAAAAAAAGH\n"; //guess what =]
					break;
				default:
					break;
				}
				powerups.erase(powerups.begin() + i);
			}
		}

		view.setCenter(player.getPos()); //center the screen on the player
	}
	//death animation
	else if (!levelWon && timer.getElapsedTime().asMilliseconds() >= 1500)
	{
		if (!player.isAlive())
		{
			viewSlideStart = player.getPos();
			player.respawn();
		}

		if(timer.getElapsedTime().asMilliseconds() < 2000)
		{
			view.setCenter(easeInOut(viewSlideStart, player.getPos(),
				(timer.getElapsedTime().asMilliseconds() - 1500) / 500.f)); //sliding view
		}
		else
		{
			player.ready();
		}
	}

	//end of level goal animation
	if (levelWon && timer.getElapsedTime().asMilliseconds() <= 2500)
	{
		if (timer.getElapsedTime().asMilliseconds() < 1500 && timer.getElapsedTime().asMilliseconds() >= 500)
		{
			view.setCenter(easeInOut(viewSlideStart, goal.getPos(), (timer.getElapsedTime().asMilliseconds() - 500) / 1000.f));
		}
	}
	else if (levelWon)
	{
		return ExitCondition::WIN;
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
	goal.drawTo(window);
	player.drawTo(window);
}