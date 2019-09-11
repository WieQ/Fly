#include "pch.h"
#include "Boss1.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
Boss1::Boss1(sf::FloatRect w)
{
	startpoint = sf::Vector2<float>(250,-50);
	currentposition = startpoint;
	world = w;

	TBoss.loadFromFile("Boss/1/Boss.png");
	SBoss.setTexture(TBoss);
	SBoss.setOrigin(13, 19);
	SBoss.setPosition(startpoint);
	

	ProCount = 0;
	MaxCount = 1000;
	pro.resize(MaxCount);

	cd = 0;
	cd2 = 0;
	
	Health = 2000;
	alive = true;
	path = 0;
	status = 0;
	series = 0;
	speed = 2;
	setMovement(sf::Vector2f(250.0f, 100.0f));
	saved_shot_target = sf::Vector2f(0.0, 0.0);
	prosprite = 1;
	
}
Boss1::~Boss1()
{
	for(unsigned int i = 0 ; i < MaxCount; i++)
		if (pro[i] != nullptr)
			delete pro[i];
	pro.clear();
}

void Boss1::Tick(sf::Vector2f T)
{
	shot_target = T;
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
	if(alive)
	{
		switch (status)
		{
		case 0:
			Moving();
			if (ReachedGoal())
			{
				status++;
				next_path = 0;
				break;
			}

			break;
		case 1:
			if (Health <= 1000)
			{
				status++;
				setMovement(sf::Vector2f(250, 100));
			}
			if (ReachedGoal())
			{
				switch (path)
				{
				case 0:	
						shoting_1_stage();
					if (next_path-- == 0)
					{
						if (shoot_type++ == 3)
							shoot_type = 1;
						setMovement(sf::Vector2<float>(100, 150));
						next_path = 90;
						cd = 0;
						path++;
					}
					break;
				case 1:
						shoting_1_stage();
					if (next_path-- == 0)
					{
						if (shoot_type++ == 3)
							shoot_type = 1;
						setMovement(sf::Vector2<float>(120, 200));
						next_path = 90;
						cd = 0;
						path++;
					}
					break;
				case 2:
						shoting_1_stage();
					if (next_path-- == 0)
					{
						if (shoot_type++ == 3)
							shoot_type = 1;
						setMovement(sf::Vector2<float>(400, 150));
						next_path = 90;
						cd = 0;
						path++;
					}
					break;
				case 3:
						shoting_1_stage();
					if (next_path-- == 0)
					{
						if (shoot_type++ == 3)
							shoot_type = 1;
						setMovement(sf::Vector2<float>(250, 100));
						next_path = 90;
						cd = 0;
						path = 0;
					}
					break;
				}
				
			}
			if (!ReachedGoal())
			{
				Moving();
			}
			break;
		case 2:
			
			if (ReachedGoal())
					shoting_2_stage();
			else
				Moving();
			break;
		}
	}
	else
	{
		SBoss.setPosition(0.0f, 0.0f);
	}
}

void Boss1::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	if (alive && SBoss.getGlobalBounds().intersects(world))
	{
		target.draw(SBoss);
	}
	for (unsigned int i = 0; i < MaxCount; ++i)
	{
		if (pro[i] != nullptr)
		{
			if (pro[i]->GetCollision().intersects(world))
				target.draw(*pro[i]);
		}
	}
}
// Every Movement Function
void Boss1::setMovement(sf::Vector2f Target)
{
	startpoint = SBoss.getPosition();
	sf::Vector2f tan = Target - startpoint;

	road = tan;
	road.x = road.x > 0 ? road.x : road.x *-1;
	road.y = road.y > 0 ? road.y : road.y *-1;
	float alpha = atan2(tan.y, tan.x);
	moving = sf::Vector2f(cos(alpha) * speed, sin(alpha) * speed);
	if (startpoint.y == Target.y)
		moving.y = 0;
	road_speed.x = moving.x < 0 ? moving.x *-1 : moving.x;
	road_speed.y = moving.y < 0 ? moving.y *-1 : moving.y;
}

bool Boss1::ReachedGoal()
{
	return road.x > 0 || road.y > 0 ? 0 : 1;
}

void Boss1::Moving()
{
	SBoss.move(moving);
	road -= road_speed;
}

void Boss1::Damage(int D)
{
	if (Health > 0)
		Health -= D;
	if (Health <= 0)
	{
		alive = false;
	}
}
bool Boss1::ShotCollision(sf::FloatRect a)
{
	sf::FloatRect boundigBox;

	for (unsigned int i = 0; i < MaxCount; ++i)
	{
		if (pro[i] != nullptr)
		{
			if (pro[i]->isActive())
			{
				boundigBox = pro[i]->GetCollision();
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

//Shot functions
void Boss1::shoting_1_stage()
{
	
	if (cd-- <= 0)
	{
		if (shoot_type != 3)
			saved_shot_target = sf::Vector2f(0.0,0.0);
		if (shot_target != sf::Vector2f(0.0, 0.0))
		{
			sf::Vector2f tan = shot_target - SBoss.getPosition();
			float alpha = atan2(tan.y, tan.x);
			switch (shoot_type)
			{
			case 1:
				for (double i = 0.0; i < 3.3; i += 0.1)
				{
					if (ProCount >= MaxCount)
						ProCount = 0;
					if (pro[ProCount] != nullptr)
						delete pro[ProCount];
					pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha + i) * 2, cos(alpha + i) * 2);
					if (ProCount >= MaxCount)
						ProCount = 0;
					if (pro[ProCount] != nullptr)
						delete pro[ProCount];
					pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha - i) * 2, cos(alpha - i) * 2);
					cd = 45;
				}
				break;
			case 2:
				for (double i = 0.0; i < 0.6; i += 0.1)
				{
					if (ProCount >= MaxCount)
						ProCount = 0;
					if (pro[ProCount] != nullptr)
						delete pro[ProCount];
					pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha + i) * 2.5, cos(alpha + i) * 2.5);
					if (ProCount >= MaxCount)
						ProCount = 0;
					if (pro[ProCount] != nullptr)
						delete pro[ProCount];
					pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha - i) * 2.5, cos(alpha - i) * 2.5);
					cd = 22;
				}
				break;
			case 3:
				if (saved_shot_target == sf::Vector2f(0.0, 0.0))
					saved_shot_target = shot_target;
				tan = saved_shot_target - SBoss.getPosition();
				alpha = atan2(tan.y, tan.x);
				if (next_path == 0)
					prosprite = 3;
				switch (prosprite)
				{
				case 1:
					for (double i = 0.0; i < 1.2; i += 0.2)
					{

						if (ProCount >= MaxCount)
							ProCount = 0;
						if (pro[ProCount] != nullptr)
							delete pro[ProCount];

						pro[ProCount++] = new BaseProjectile("Character/Projectiles/BarProjectile/1.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha + i) * 3, cos(alpha + i) * 3, (alpha+i) * 180 / 3.14 - 90);

						if (ProCount >= MaxCount)
							ProCount = 0;
						if (pro[ProCount] != nullptr)
							delete pro[ProCount];
						pro[ProCount++] = new BaseProjectile("Character/Projectiles/BarProjectile/1.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha - i) * 3, cos(alpha - i) * 3,(alpha-i) * 180 / 3.14 - 90);
						
					}
					cd = 2;
					prosprite++;
					break;
				case 2:
					for (double i = 0.0; i < 1.2; i += 0.2)
					{

						if (ProCount >= MaxCount)
							ProCount = 0;
						if (pro[ProCount] != nullptr)
							delete pro[ProCount];
							pro[ProCount++] = new BaseProjectile("Character/Projectiles/BarProjectile/2.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha + i) * 3, cos(alpha + i) * 3, (alpha+i) * 180 / 3.14 - 90);

						if (ProCount >= MaxCount)
							ProCount = 0;
						if (pro[ProCount] != nullptr)
							delete pro[ProCount];
						pro[ProCount++] = new BaseProjectile("Character/Projectiles/BarProjectile/2.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha - i) * 3, cos(alpha - i) * 3, (alpha-i) * 180 / 3.14 - 90);
						
					}
					
					cd = 2;
					break;
				case 3:
					for (double i = 0.0; i < 1.2; i += 0.2)
					{

						if (ProCount >= MaxCount)
							ProCount = 0;
						if (pro[ProCount] != nullptr)
							delete pro[ProCount];
							pro[ProCount++] = new BaseProjectile("Character/Projectiles/BarProjectile/3.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha + i) * 3, cos(alpha + i) * 3, (alpha+i) * 180 / 3.14 - 90);

						if (ProCount >= MaxCount)
							ProCount = 0;
						if (pro[ProCount] != nullptr)
							delete pro[ProCount];
						pro[ProCount++] = new BaseProjectile("Character/Projectiles/BarProjectile/3.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha - i) * 3, cos(alpha - i) * 3, (alpha-i) * 180 / 3.14 - 90);

					}
					cd = 2;
					prosprite = 1;
					break;
				}
				
				break;
			}
		}
	}

}

void Boss1::shoting_2_stage()
{
	sf::Vector2f tan;
	double alpha;
	
	if (cd-- <= 0)
	{
		sf::Vector2f pstart;
		sf::Vector2f pgoal;
		
		
		for (int i = 0; i < 2; i++)
		{
			pstart = sf::Vector2f(rand() % 60 + 220, rand() % 60 + 90);
			pgoal = sf::Vector2f(rand() % 800 + 1, rand() % 600 + 1);
			tan = pgoal - SBoss.getPosition();
			alpha = atan2(tan.y, tan.x);
			if (ProCount >= MaxCount)
				ProCount = 0;
			if (pro[ProCount] != nullptr)
				delete pro[ProCount];
			pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile1.png", sf::Vector2f(6, 6), SBoss.getPosition(), sin(alpha) * 2, cos(alpha) * 2,alpha *180/3.14 -90);
		}
		cd = 1;
	}
	if (cd2-- <= 0)
	{
		tan = shot_target - SBoss.getPosition();
		alpha = atan2(tan.y, tan.x);
		for (double i = 0.0; i < 3.3; i += 0.1)
		{
			
			if (ProCount >= MaxCount)
				ProCount = 0;
			if (pro[ProCount] != nullptr)
				delete pro[ProCount];
			pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha + i) * 3, cos(alpha + i) * 3);
			if (ProCount >= MaxCount)
				ProCount = 0;
			if (pro[ProCount] != nullptr)
				delete pro[ProCount];
			pro[ProCount++] = new BaseProjectile("Character/Projectiles/BossProjectile3.png", sf::Vector2f(6, 6), sf::Vector2f(SBoss.getPosition().x, SBoss.getPosition().y), sin(alpha - i) * 3, cos(alpha - i) * 3);
			
		}
		cd2 = 30;
	}
}