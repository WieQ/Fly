#pragma once
#ifndef POWERUP_H_
#define POWERUP_H_
#include "SFML/Graphics.hpp"
class PowerUp : public sf::Drawable
{
private:
	sf::Texture TPowerUp;
	sf::Sprite SPowerUp;
	int change_speed;
	float speedy;
public:
	PowerUp() {};
	PowerUp(sf::Vector2f spawn);
	void Tick();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	bool CharacterCollision(sf::FloatRect c) const;
};
#endif // !POWERUP_H_
