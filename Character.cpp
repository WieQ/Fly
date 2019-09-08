#include "pch.h"
#include <iostream>
#include "Character.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window.hpp"



Character::Character(sf::FloatRect w): direction(true)
{
	
	canmoveleft = false;
	canmoveright = false;
	shoot = false;
	alive = true;

	world = w;

	speed = 4;

	ProCount = 0;
	MaxCount = 100;
	pro.resize(MaxCount);

	cd = 0;
	wsprite = 0;

	HitBox.loadFromFile("Character/HitBox3.png");
	SHitBox.setTexture(HitBox);
	CSlowDown = SHitBox.getColor();
	CHitBox = sf::Color(76, 0, 130);
	SHitBox.setColor(CHitBox);
	SHitBox.setOrigin(2, 2);
	

	Teleport.loadFromFile("Character/Teleport.png");
	STeleport.setTexture(Teleport);
	STeleport.setOrigin(13,19);
	Idle.loadFromFile("Character/Idle.png");
	SIdle.setTexture(Idle);
	CurrentSprite = SIdle;
	CurrentSprite.setOrigin(13, 19);
	CurrentSprite.setScale(1, 1);

	

	moving = sf::Vector2<float>(0.0f, 0.0f);
	startpoint = sf::Vector2<float>(250.0f,500.0f);
	CurrentSprite.setPosition(startpoint);
	SHitBox.setPosition(250.0f, 492.0f);
	teleportposition = startpoint;
	

	isMovingX = false;
	isMovingY = false;
}
//Function called every frame
void Character::Tick(sf::Vector2f Target)
{
	//Teleport to shadow
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		teleportposition = CurrentSprite.getPosition();
		STeleport.setPosition(CurrentSprite.getPosition());
		teleport_viable = true;
	}
	if (teleport_viable && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		CurrentSprite.setPosition(teleportposition);
		SHitBox.setPosition(teleportposition.x,teleportposition.y-8);
		teleport_viable = false;
		if (!alive)
			alive = true;
	}
	if (alive)
	{
		IsNearBorder();
		SlowDown();
		isMovingX = MoveX();
		isMovingY = MoveY();
		
		if (!isMovingX && !isMovingY)
		{
			switch (wsprite++)
			{
			case 10:
				Idle.loadFromFile("Character/Idle.png");
				break;
			case 20:
				Idle.loadFromFile("Character/Idle1.png");
				break;
			case 30:
				Idle.loadFromFile("Character/Idle.png");
				break;
			case 40:
				Idle.loadFromFile("Character/Idle2.png");
				wsprite = 0;
				break;
			}
		}
		SIdle.setTexture(Idle);
		if (ProCount > 0)
			for (unsigned int i = 0; i < MaxCount; ++i)
				if(pro[i] != nullptr)
					pro[i]->Tick();
		if (cd <= 0)
			Shoting(Target);
		else
			cd--;

		//Character Movement
	
		SetPosition();
	}
	else
	{
		CurrentSprite.setPosition(0.0f, 0.0f);
		SHitBox.setPosition(0.0f, 0.0f);
	}
}

//Horizontal Movement
bool Character::MoveX()
{
	if (canmoveleft && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		moving.x = -speed;
		direction = false;
		Idle.loadFromFile("Character/Idle.png");
		return true;
	}
	else if (canmoveright && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moving.x = speed;
		direction = true;
		Idle.loadFromFile("Character/Idle.png");
		return true;
	}
	return false;
}

//Vertical Movement
bool Character::MoveY()
{
	if (canmoveup && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moving.y = -speed;
		Idle.loadFromFile("Character/Idle.png");
		return true;

	}
	else if (canmovedown && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moving.y = speed;
		Idle.loadFromFile("Character/Idle.png");
		return true;
	}
	return false;
}
//Chceking if we are near the border, if yes we no longer can move in that direction
void Character::IsNearBorder()
{
	canmoveleft = (CurrentSprite.getPosition().x > 64.0f) ? true : false;
	canmoveright = (CurrentSprite.getPosition().x < 439.0f) ? true : false;
	canmoveup = (CurrentSprite.getPosition().y > 70.0f) ? true:false;
	canmovedown = (CurrentSprite.getPosition().y < 530.0f) ? true : false;
	
}		
//Setiing Character Position there is a lot thing we want to setup.
bool Character::SetPosition()
{
	if (alive)
	{
		CurrentSprite.move(moving);
		SHitBox.move(moving);
		moving = sf::Vector2<float>(0.0f, 0.0f);
		return true;
	}

}

//inherited methods which draw character on window
void Character::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	if (alive)
	{
		if (teleport_viable)
			target.draw(STeleport, states);
		target.draw(CurrentSprite, states);
		target.draw(SHitBox, states);
		
		if (MaxCount > 0)
			for (unsigned int i = 0; i < MaxCount; ++i)
			{
				if (pro[i] != nullptr && pro[i]->GetCollision().intersects(world))
					target.draw(*pro[i], states);
			}
	}
}

//Checking if we are pressing shift button and if we do reducing movemnt speed
void Character::SlowDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		speed = 1.5;
		SHitBox.setColor(CSlowDown);
	}
	else
	{
		speed = 4;
		SHitBox.setColor(CHitBox);
	}
}

//Shooting function
void Character::Shoting(sf::Vector2f T)
{
	//shooting whenever you press Z 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		//checking if we aren't overflowing
			if (ProCount >= MaxCount)
				ProCount = 0;
		//if pointer isn't we want to delete that projectile
			if (pro[ProCount] != nullptr)
				delete pro[ProCount];
		//we are asigning new Projectile to pointer and then we are doing increment
			pro[ProCount++] =  new BaseProjectile("Character/Projectiles/classic4.png", sf::Vector2f(6, 6), sf::Vector2f(SHitBox.getPosition().x, SHitBox.getPosition().y - 20), -7,-0.5 );
		//checking if we aren't overflowing
			if (ProCount >= MaxCount)
				ProCount = 0;
			//if pointer isn't we want to delete that projectile
			if (pro[ProCount] != nullptr)
				delete pro[ProCount];
			//we are asigning new Projectile to pointer and then we are doing increment
			pro[ProCount++] = new BaseProjectile("Character/Projectiles/classic4.png",sf::Vector2f(6,6), sf::Vector2f(SHitBox.getPosition().x, SHitBox.getPosition().y - 20), -7,0.5);
		
		//last projectile is different so it's shooting from teleport location so if we leave our shadow somewhere projectile will be flying from shadow
				if (ProCount >= MaxCount)
					ProCount = 0;
				if (pro[ProCount] != nullptr)
					delete pro[ProCount];
				pro[ProCount++] = new BaseProjectile("Character/Projectiles/classic4.png", sf::Vector2f(6, 6), teleport_viable == true ? sf::Vector2f(STeleport.getPosition().x, STeleport.getPosition().y -22): sf::Vector2f(SHitBox.getPosition().x, SHitBox.getPosition().y - 20), -7, 0);
		//coldown showing us when we can shoot again  
		cd = 5;
	}
}

//Collision with bullets from enemies
bool Character::shotcollision(sf::FloatRect a)
{
	// creating floatingRect bounding box to compare it with enemy bounding box
	sf::FloatRect boundigBox;
	for (unsigned int i = 0; i < MaxCount; ++i)
	{
		if (pro[i] != nullptr && pro[i]->isActive())
		{
			boundigBox = pro[i]->GetSprite().getGlobalBounds();
			if (pro[i]->GetSprite().getPosition().y > 0 && a.intersects(boundigBox))
			{
				delete pro[i];
				pro[i] = nullptr;
				return true;
			}
		}
	}
	return false;
} 

// Colision with Enemies
bool Character::charactercollision(sf::FloatRect a)
{
	// creating colision box based on HitBox Sprite
	sf::FloatRect boundigBox = SHitBox.getGlobalBounds();
	
	//whenever enemies is inside HitBox Collision spot we are returning true
	if (a.intersects(boundigBox))
	{
		return true;
	}
	return false;
}

//Damaging Character always based on Collision function so whenever
//Collision function is called we shot call this function afterwards
bool Character::Damage()
{
	teleport_viable = false;
	return alive = false;
	
}