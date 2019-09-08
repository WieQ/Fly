#ifndef BASEENEMY_H_
#define BASEENEMY_H_
#include "SFML/Graphics.hpp"
#include "BaseProjectile.h"

class BaseEnemy : public sf::Drawable
{
protected:
	// setting up 
	sf::Vector2f moving;
	sf::Vector2f startpoint;
	sf::Vector2f currentposition;
	sf::Vector2f road;
	sf::Vector2f road_speed;
	sf::Vector2f goal;
	sf::Vector2f flyout;

	float speed;

	sf::Texture TBaseEnemy;
	sf::Sprite SBaseEnemy;
	sf::FloatRect world;

	std::vector<BaseProjectile*> pro;
	unsigned int ProCount;
	unsigned int MaxCount;
	short shooting_style;
	sf::Vector2f shoot_target;
	int cd;
	int Health;
	short status;
	short series;

	bool alive;

public:
	BaseEnemy() { alive = false; }
	BaseEnemy(std::string p /*path to sprite*/,sf::Vector2f sp/*startpoint*/,
		sf::Vector2f g /*goal*/, sf::Vector2f f /*flyout*/,sf::FloatRect w /*World*/,
		int hp = 10, float ms = 1.0f/*movement speed*/, short s = 0 /*shooting style*/);
	~BaseEnemy();
	virtual void Tick(sf::Vector2f T);
	
	sf::FloatRect GetCollision() { return SBaseEnemy.getGlobalBounds(); }
	void Damage(int D);
	bool ShotCollision(sf::FloatRect target);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	virtual void setMovement(sf::Vector2f Target);
	virtual void Shoting();
	virtual bool ReachedGoal();
	virtual void Moving();
};

#endif // !BASEENEMIES_H_
