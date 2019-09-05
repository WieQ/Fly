#ifndef CHARACTER_H_ 
#define CHARACTER_H_ 

#include "pch.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include <vector>
#include "BaseProjectile.h"

class Character: public sf::Drawable
{
private:
	//stage collision to detect drawable contet like projecitle z
	sf::FloatRect world;
	//Positions;
		sf::Vector2<float> moving;
		sf::Vector2f currentposition;
		sf::Vector2<float> teleportposition;
		sf::Vector2<float> startpoint;
	
	//Textures;
		sf::Texture Idle;
		sf::Texture HitBox;
		sf::Texture Teleport;
	//Color
		sf::Color CHitBox;
	
	//Sprite
		sf::Sprite SIdle;
		sf::Sprite CurrentSprite;
		sf::Sprite SHitBox;
		sf::Sprite STeleport;
	// Sprite status Moving or flying
		int wsprite;
	//Projectile array (vector type)
		std::vector<BaseProjectile*> pro;
	//Projectile status and size;
		unsigned int ProCount;
		unsigned int MaxCount;
	//Projectile cooldown
	int cd;
	
	//Flying speed
	float speed;

	//Position bool
	bool canmoveleft;
	bool canmoveright;
	bool canmoveup;
	bool canmovedown;

	//Position and Moving Functions
	bool isMovingX;
	bool isMovingY;
	void IsNearBorder();
	void SlowDown();

	//Status Bools
	bool shoot;
	bool alive;
		
	//Status Function
	void Shoting(sf::Vector2f T);
	bool direction;
	bool lastdirection;
	bool MoveX();
	bool MoveY();
	
	//bool Teleport
	bool teleport_viable;
	class Animation* Walk;

public:
	Character(sf::FloatRect w);
	void Tick(sf::Vector2f Target);
	bool SetPosition();
	sf::Sprite& GetCurrentSprite() { return CurrentSprite; };
	sf::FloatRect GetHitbox() { return SHitBox.getGlobalBounds(); }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	sf::Vector2f GetCharacterPos() { return SHitBox.getPosition(); } 
	//Colission Functions
	bool shotcollision(sf::FloatRect a);
	bool charactercollision(sf::FloatRect a);
	bool Damage();
};
#endif