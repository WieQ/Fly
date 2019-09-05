#pragma once
#ifndef PARABOLEENEMY_H_
#define PARABOLEENEMY_H_
#include "BaseEnemy.h"
class ParaboleEnemy :public BaseEnemy
{
private:
public:
	ParaboleEnemy(std::string p /*path to sprite*/, sf::Vector2f sp/*startpoint*/,
		sf::Vector2f g /*goal*/, sf::Vector2f f /*flyout*/, sf::FloatRect w /*World*/, 
		int hp = 10, float ms = 1.0f/*movement speed*/, short s = 0 /*shooting style*/);
};
#endif // !PARABOLEENEMY_H_
