#include "pch.h"
#include "BaseEnemy.h"
#include <iostream>


BaseEnemy::BaseEnemy(std::string p,sf::Vector2f sp/*startpoint*/, sf::Vector2f f /*flyout*/, sf::FloatRect w /*World*/, int hp, float ms/*movement speed*/, short s/*shooting style*/)
{
	alive = true;

	startpoint = sp;
	currentposition = startpoint;
	flyout = f;
	TBaseEnemy.loadFromFile(p);
	SBaseEnemy.setTexture(TBaseEnemy);
	SBaseEnemy.setOrigin(13, 19);
	SBaseEnemy.setPosition(currentposition);
	speed = ms;
	setMovement(flyout);
	Health = hp;
	shooting_style = s;
	status = 0;
	cd = 0; 
	series = 0;
	ProCount = 0;
	MaxCount = 200;
	pro.resize(MaxCount);
	world = w;
}

BaseEnemy::~BaseEnemy()
{

	for (size_t i = 0; i < MaxCount; i++)
	{
		if (pro[i] != nullptr)
			delete pro[i];
	}
	pro.clear();
}

void BaseEnemy::Tick(sf::Vector2f T)
{
	target_position = T;
	if (ProCount > 0)
	{
		for (unsigned int i = 0; i < MaxCount; ++i)
		{
			if (pro[i] != nullptr)
			{
				pro[i]->Tick();
				if (!world.intersects(pro[i]->GetCollision()))
				{
					delete pro[i];
					pro[i] = nullptr;
				}
			}
		}
	}
	if (alive)
	{
		if(cd-- < 1)
			Shoting();
		Moving();
	}
	else
	{
		SBaseEnemy.setPosition(0.0f, 0.0f);
	}
}

void BaseEnemy::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	if (alive && SBaseEnemy.getGlobalBounds().intersects(world))
	{
		target.draw(SBaseEnemy);
	}
	if (MaxCount > 0)
		for (unsigned int i = 0; i < MaxCount; ++i)
		{
			if (pro[i] != nullptr)
			{
				if (pro[i]->GetCollision().intersects(world))
					target.draw(*pro[i], states);
			}
		}
}

bool BaseEnemy::Damage(int D)
{
	if (Health > 0)
		Health -= D;
	if (Health <= 0)
	{
		alive = false;
		return true;
	}
	return false;
}

bool BaseEnemy::ShotCollision(sf::FloatRect a)
{

	sf::FloatRect boundigBox;
	for (unsigned int i = 0; i < MaxCount; ++i)
	{
		if (pro[i] != nullptr)
		{
			if (pro[i]->isActive())
			{
				boundigBox = pro[i]->GetSprite().getGlobalBounds();
				if (a.intersects(boundigBox))
				{
					delete pro[i];
					pro[i] = nullptr;
					return true;
				}
			}
		}
	}
	return false;
}

void BaseEnemy::setMovement(sf::Vector2f Target)
{
	startpoint = SBaseEnemy.getPosition();
	sf::Vector2f tan = Target - startpoint;

	road = tan;
	road.x = road.x > 0 ? road.x : road.x *-1;
	road.y = road.y > 0 ? road.y : road.y *-1;
	double alpha = atan2(tan.y, tan.x);
	moving = sf::Vector2f(cos(alpha) * speed, sin(alpha) * speed);
	if (startpoint.y == Target.y)
		moving.y = 0;
	road_speed.x = moving.x < 0 ? moving.x *-1 : moving.x;
	road_speed.y = moving.y < 0 ? moving.y *-1 : moving.y;
}

bool BaseEnemy::ReachedGoal()
{
	return road.x > 0 || road.y > 0 ? 0 : 1;
}

void BaseEnemy::Moving()
{
	SBaseEnemy.move(moving);
	currentposition = SBaseEnemy.getPosition();
	road -= road_speed;
}

void BaseEnemy::Shoting()
{
	if (target_position != sf::Vector2f(0.0, 0.0))
	{
		sf::Vector2f tan = target_position - SBaseEnemy.getPosition();
		double alpha = atan2(tan.y, tan.x);

		switch (shooting_style)
		{
		case 1:
			if (ProCount >= MaxCount)
				ProCount = 0;
			delete pro[ProCount];
			pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBaseEnemy.getPosition().x, SBaseEnemy.getPosition().y + 25), sin(alpha) * 2, cos(alpha) * 2);
			cd = 20;
			break;

		case 2:

			for (double i = 0.0; i < 0.4; i += 0.2)
			{
				if (ProCount >= MaxCount)
					ProCount = 0;
				if (pro[ProCount] != nullptr)
					delete pro[ProCount];
				pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBaseEnemy.getPosition().x, SBaseEnemy.getPosition().y), sin(alpha + i) * 2, cos(alpha + i) * 2);
				if (ProCount >= MaxCount)
					ProCount = 0;
				if (pro[ProCount] != nullptr)
					delete pro[ProCount];
				pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBaseEnemy.getPosition().x, SBaseEnemy.getPosition().y), sin(alpha - i) * 2, cos(alpha - i) * 2);
				cd = 45;

			}
		}

	}
}