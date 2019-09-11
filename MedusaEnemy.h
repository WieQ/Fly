#ifndef MEDUSAENEMY_H_
#define MEDUSAENEMY_H_

#include"BaseEnemy.h"

class MedusaEnemy : public BaseEnemy
{
private:
	int flipbook;
	bool move;
	virtual void setMovement(sf::Vector2f Target);//Base
public:
	MedusaEnemy() :BaseEnemy() {}
	MedusaEnemy(std::string p /*path to sprite*/, sf::Vector2f sp/*startpoint*/,
		sf::Vector2f f /*flyout*/, sf::FloatRect w /*World*/,
		int hp = 10, float ms = 1.0f/*movement speed*/, short s = 0 /*shooting style*/) : BaseEnemy(p, sp, f, w, hp, ms, s), flipbook(0), move(false)
	{
		setMovement(flyout);
	}
	virtual void Tick(sf::Vector2f T);
};
#endif // !MEDUSAENEMY_H_
