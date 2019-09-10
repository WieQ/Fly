#include "pch.h"
#include "OneStopEnemy.h"
#include <iostream>


OneStopEnemy::OneStopEnemy(std::string p, sf::Vector2f sp/*startpoint*/, sf::Vector2f g /*goal*/, sf::Vector2f f /*flyout*/, sf::FloatRect w /*World*/, int hp, float ms/*movement speed*/, short s/*shooting style*/): BaseEnemy(p,sp,f,w,hp,ms,s)
{
	goal = g;
	setMovement(goal);
}

void OneStopEnemy::Tick(sf::Vector2f T)
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
		if (cd-- <= 0 && shooting_style == 1)
			Shoting();
		switch (status)
		{
		case 0:
			Moving();
			if (ReachedGoal())
				status++;
			break;
		case 1:
			if (cd-- <= 0 && shooting_style > 1)
				Shoting();
			if (series++ == 80)
			{
				status++;
				setMovement(flyout);
			}
			break;
		case 2:
			Moving();
			break;
		}
	}
	else
	{
		SBaseEnemy.setPosition(0.0f, 0.0f);
	}
}

void OneStopEnemy::Shoting()
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