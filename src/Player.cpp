#include "Player.h"


Player::Player()
{
	circ.setFillColor(sf::Color::Cyan);
	circ.setRadius(30.f);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
    spinner.setSize(sf::Vector2f(50, 16));
    spinner.setFillColor(sf::Color::Cyan);
    spinner.setOrigin(0, 8);
}


void Player::update(sf::RenderWindow& window)
{
    float theta; //angle between mouse and player, different than the angle member which is used for velocity
    sf::Vector2f mouseMap, d;

    //not super nessecary to put in the alive, just optimization
    if (alive && !levelWon)
    {
        mouseMap = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        d = mouseMap - circ.getPosition();

        theta = angleOf(mouseMap, circ.getPosition());

        //aims the spinner at the cursor
        spinner.setRotation(theta * 180 / 3.14159); //convert to degrees lol


        if (active)
        {
            //changes movement based on the current mode
            if (slideMode)
            {
                if (!isButtonPressed(sf::Mouse::Left) && mousePressed)
                {
                    if (warpActive)
                    {
                        circ.setPosition(mouseMap);
                        //instantly warp player and have view catch up (fast, slide math for easing????????)
                        warpActive = false;
                    }
                    else
                    {
                        vel.x = d.x / ((FRAMERATE + 1) / 2.f); //okay i dont like magic code but i actually do not know the explanation
                        vel.y = d.y / ((FRAMERATE + 1) / 2.f); //also this is the only case where it makes more sense to directly set vel than use angle and magnitude
                        frictionVel = vel;
                    }
                }
            }
            else
            {
                angle = theta; //will now move player toward the mouse
                magnitude = 10; //at a constant speed
                updateVelocity();

                if (warpActive && !isButtonPressed(sf::Mouse::Left) && mousePressed)
                {
                    circ.setPosition(mouseMap);
                    //instantly warp player and have view catch up (fast, slide math for easing????????)
                    warpActive = false;
                }

                if (boostTimer.getElapsedTime().asMilliseconds() >= 2000)
                {
                    slideMode = true;
                }
            }


            //used for checking when a release has happened
            if (isButtonPressed(sf::Mouse::Left))
                mousePressed = true;
            else
                mousePressed = false;
        }
            
        prevPos = circ.getPosition();

        //moves the player if it has velocity
        if (vel.x != 0 && vel.y != 0)
        {
            circ.setPosition(circ.getPosition() + vel);
            if (slideMode)
                decelerate();
        }

        spinner.setPosition(circ.getPosition());
    }
}


bool Player::isTouching(Wall wall)
{
    double a, b, c, beta, gamma;

    for (int i = 0; i < wall.getWallCount(); i++)
    {
        a = distBetween(wall.getPoint(i), wall.getPoint(i + 1));
        b = distBetween(circ.getPosition(), wall.getPoint(i));
        c = distBetween(circ.getPosition(), wall.getPoint(i + 1));

        beta = lawOfCos(a, c, b);
        gamma = lawOfCos(a, b, c);

        if ((b < circ.getRadius() || c < circ.getRadius()) //if the point is inside the circle
            || (gamma <= PI / 2.f && beta <= PI / 2.f //or if both angles are acute
            && b * sin(gamma) < circ.getRadius())) //and the height of triangle abc < radius...
        {
            return true;
        }
    }

    return false;
}


bool Player::hasCrossed(Wall wall)
{
    int intersectCount = 0;
    float a = 0, b = 0;
    sf::Vector2f intersect;

    for (int i = 0; i < wall.getWallCount(); i++)
    {
        //finding the theoretical intersection point of the wall and the
        //line between the previous and current player positions.
        //this math is a little crazy and hard to follow but it works.
        
        //getting the angles i need for the intersection (the first angle is only needed to determine the third)
        a = lawOfCos(prevPos, getPos(), wall.getPoint(i));
        b = lawOfCos(wall.getPoint(i), wall.getPoint(i + 1), prevPos); 
        a = 180 - a - b; //angle opposite from the line we know

        //law of sines to solve for the side length
        b = sin(b) * distBetween(prevPos, wall.getPoint(i)) / sin(a); //swap sin(a) and sin(b)???
        
        //setting the intersect point based on the length
        intersect = prevPos;
        a = angleOf(prevPos, getPos());
        intersect.x += b * cos(a);
        intersect.y += b * sin(a);

        //intersection must be on the line, check if it is between start and end
        if (prevPos.x != getPos().x) //checking if the wall is vertical
        {
            if ((prevPos.x < intersect.x) == (intersect.x < getPos().x)) //the == is a XNOR :O
            {
                intersectCount++; //counting the total walls that the player would have crosseed through
            }
        }
        else if ((prevPos.y < intersect.y) == (intersect.y < getPos().y)) 
        {
            intersectCount++;
        }
    }

    return intersectCount % 2 == 1; //if the 
}


bool Player::isTouching(Collectible collect)
{
    //gotta love how comically easy this is compared to the wall collision
    return distBetween(collect.getPos(), getPos()) <= circ.getRadius() + collect.getRadius();
}


bool Player::isTouching(Goal goal)
{
    return distBetween(goal.getPos(), getPos()) <= circ.getRadius() + goal.getRadius();
}

void Player::drawTo(sf::RenderWindow& window)
{
    if (alive)
    {
	    window.draw(spinner);
	    window.draw(circ);
    }
}


void Player::decelerate()
{
    //if the next velocity change would result in it flipping signs, 
    //that means it is done running and should be set to 0
    if (abs(vel.x) >= abs(frictionVel.x) / FRAMERATE && abs(vel.y) >= abs(frictionVel.y) / FRAMERATE)
    {
        vel.x -= frictionVel.x / FRAMERATE; //should take exactly one second to slide
        vel.y -= frictionVel.y / FRAMERATE;
    }
    else
        vel.x = vel.y = 0;
}


void Player::updateVelocity()
{
	vel.x = magnitude * cos(angle);
	vel.y = magnitude * sin(angle);
    frictionVel = vel;
}