#pragma once
#ifndef ONESTOPENEMY_H_
#define ONESTOPENEMY_H_
#include "BaseEnemy.h"

class OneStopEnemy : public BaseEnemy
{
protected:
	sf::Vector2f goal;
	virtual void Tick(sf::Vector2f T);
	virtual void Shoting();
public:
	OneStopEnemy() : BaseEnemy() {}
	OneStopEnemy(std::string p /*path to sprite*/, sf::Vector2f sp/*startpoint*/,
		sf::Vector2f g /*goal*/, sf::Vector2f f /*flyout*/, sf::FloatRect w /*World*/,
		int hp = 10, float ms = 1.0f/*movement speed*/, short s = 0 /*shooting style*/);
};
#endif // !ONESTOPENEMY_H_