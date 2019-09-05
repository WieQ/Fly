#include "pch.h"
#include "SinusProjectile.h"
#include <iostream>
#include <cmath>

SinusProjectile::SinusProjectile(std::string p, sf::Vector2f Op, sf::Vector2<float> po, float Ysp , float SinLimit) :BaseProjectile(p, Op, po, Ysp)
{
	
	sinuslimit = -0.05f * SinLimit;
	sinus = 0.0f;
	speed.x = 1; 
	sinuschangesign = 2;
	sincount = 0;
}

void SinusProjectile::Tick()
{
	if (active)
	{	
		Sprojectile.move(speed);
		speed.x = sin(sinus)* sinuschangesign;
		sinus += sinuslimit;
	}
}

SinusProjectile SinusProjectile::operator=(SinusProjectile s)
{
	if (this == &s)
		return *this;

	BaseProjectile::operator=(s);
	sinus = s.sinus;
	sinuschangesign = s.sinuschangesign;
	sinuslimit = s.sinuslimit;
	return *this;
}