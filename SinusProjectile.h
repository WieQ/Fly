#ifndef SinusProjectile_H_
#define SinusProjectile_H_
#include "BaseProjectile.h"

class SinusProjectile : public BaseProjectile
{
private:
	float sinus;
	float sinuslimit;
	float sinuschangesign;
	int sincount;
public:
	SinusProjectile() : BaseProjectile() { }
	SinusProjectile(std::string p, sf::Vector2f Op, sf::Vector2<float> po, float Ysp,float SinLimit);
	virtual void Tick();
	virtual SinusProjectile operator=(SinusProjectile s);
};
#endif // !SinusProjectile_H_
