#include "pch.h"
#include "BaseProjectile.h"
#include <iostream>

BaseProjectile::BaseProjectile(std::string p, sf::Vector2f Op, sf::Vector2<float> po, float Ysp, float Xsp )
{
	path = p;
	projectile.loadFromFile(path);
	Sprojectile.setTexture(projectile);
	position = po;
	Sprojectile.setPosition(position);
	Sprojectile.setOrigin(Op);

	speed.y = Ysp;
	speed.x = Xsp;

	ProjectileCollision = Sprojectile.getGlobalBounds();
	active = true;
}

void BaseProjectile::Tick()
{
	if (active)
	{
		
		Sprojectile.move(speed);
	}
}
void BaseProjectile::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(Sprojectile, states);
}

BaseProjectile BaseProjectile::operator=(BaseProjectile s)
{
	if (this == &s)
		return *this;

	path = s.path;
	projectile = s.projectile;
	Sprojectile = s.Sprojectile;
	Sprojectile.setTexture(projectile);
	position = s.position;
	speed = s.speed;
	ProjectileCollision = s.ProjectileCollision;
	active = s.active;
	return *this;
}