#ifndef BASEENEMY_H_
#define BASEENEMY_H_
#include "SFML/Graphics.hpp"
#include "BaseProjectile.h"

class BaseEnemy : public sf::Drawable
{
protected:
	// setting up 
	sf::Vector2f moving; // Base
	sf::Vector2f startpoint;// Base
	sf::Vector2f currentposition; //Base
	sf::Vector2f road;//Base
	sf::Vector2f road_speed;//Base
	sf::Vector2f goal;
	sf::Vector2f flyout;//Base

	float speed;//Base

	sf::Texture TBaseEnemy;//Base
	sf::Sprite SBaseEnemy;//Base
	sf::FloatRect world;//Base

	std::vector<BaseProjectile*> pro;
	unsigned int ProCount;
	unsigned int MaxCount;
	short shooting_style;
	sf::Vector2f target_position;
	int cd;
	int Health;//Base
	short status;
	short series;

	bool alive;//Base

	virtual bool ReachedGoal();//Base
	virtual void Moving();
	virtual void setMovement(sf::Vector2f Target);//Base

public:
	BaseEnemy() { alive = false; }
	BaseEnemy(std::string p /*path to sprite*/,sf::Vector2f sp/*startpoint*/,
		sf::Vector2f f /*flyout*/,sf::FloatRect w /*World*/,
		int hp = 10, float ms = 1.0f/*movement speed*/, short s = 0 /*shooting style*/);
	~BaseEnemy();
	virtual void Tick(sf::Vector2f T);//Base
	
	sf::FloatRect GetCollision() { return SBaseEnemy.getGlobalBounds(); }//Base
	void Damage(int D);//Base
	bool ShotCollision(sf::FloatRect target);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;//Base
	virtual void Shoting();
	//Base
};

#endif // !BASEENEMIES_H_
