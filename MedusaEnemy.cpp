#include "pch.h"
#include "MedusaEnemy.h"
#include <iostream>

void MedusaEnemy::Tick(sf::Vector2f T)
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
		if (cd-- < 1)
			Shoting();
		switch (flipbook++)
		{
		case 10:
			TBaseEnemy.loadFromFile("Enemy/NMedusa/1.png");
			break;
		case 20:
			TBaseEnemy.loadFromFile("Enemy/NMedusa/2.png");
			break;
		case 30:
			TBaseEnemy.loadFromFile("Enemy/NMedusa/3.png");
			move = true;
			break;
		case 60:
			TBaseEnemy.loadFromFile("Enemy/NMedusa/4.png");
			move = false;
			flipbook = 0;
			break;
		}
		SBaseEnemy.setTexture(TBaseEnemy);
		if(move)
			Moving();
	}
	else
	{
		SBaseEnemy.setPosition(0.0f, 0.0f);
	}
}

void MedusaEnemy::setMovement(sf::Vector2f Target)
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
	SBaseEnemy.rotate(alpha * 180 / 3.14 + 90);
}