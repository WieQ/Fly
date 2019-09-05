#ifndef TargetProjectile_H_
#define TargetProjectile_H_
#include "BaseProjectile.h"

class TargetProjectile : public BaseProjectile
{
private:
	float sinus;
	float sinuslimit;
	float sinuschangesign;
	int sincount;
public:
	TargetProjectile() : BaseProjectile() { }
	TargetProjectile(std::string p, sf::Vector2f Op, sf::Vector2<float> po, float Ysp, sf::Vector2f Target) {};
	virtual void Tick() {};
	virtual TargetProjectile operator=(TargetProjectile s) {};
};
#endif // !TargetProjectile_H_
