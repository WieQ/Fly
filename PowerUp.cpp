#include "pch.h"
#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f spawn)
{
	TPowerUp.loadFromFile("Character/Projectiles/PowerUP/PU.png");
	SPowerUp.setTexture(TPowerUp);
	SPowerUp.setPosition(spawn);
	speedy = -3.0;
	change_speed = 0;
}

void PowerUp::Tick()
{
	if (speedy < 0 && change_speed++ == 15)
		speedy *= -1;
	SPowerUp.move(0.0, speedy);
}

void PowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(SPowerUp);
}

bool PowerUp::CharacterCollision(sf::FloatRect c) const
{
	sf::FloatRect boundingBox = SPowerUp.getGlobalBounds();
	if (boundingBox.intersects(c))
		return true;
	return false;
}