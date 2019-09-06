#pragma once
#ifndef  BASEPROJECTILE_H_
#define BASEPROJECTILE_H_
#include "SFML/Graphics.hpp"
#include <string>
class BaseProjectile : public sf::Drawable
{
protected:
	std::string path;
	sf::Texture projectile;
	sf::Sprite Sprojectile;
	sf::Vector2f position;
	sf::Vector2f speed;
	sf::FloatRect ProjectileCollision;
	bool active;
public:
	BaseProjectile(std::string p,sf::Vector2f Op/*OriginPoint of Projectile*/, sf::Vector2<float> po, float Ysp, float Xsp = 0, double ang = 0);
	BaseProjectile() { active = false; path = "brak"; speed.x = 0; speed.y = 0; position.x = 0; position.y = 0; };
	virtual void Tick();
	sf::Sprite GetSprite() { return Sprojectile; }
	void SetScale(float fx, float fy) { Sprojectile.setScale(fx, fy); }
	sf::FloatRect GetCollision()const { return Sprojectile.getGlobalBounds(); }
	float GetPositionY() const { return Sprojectile.getPosition().y; }
	float GetPositionX() const { return Sprojectile.getPosition().x; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	bool isActive() { return active; };
	virtual BaseProjectile operator=(BaseProjectile s);
};

#endif // ! BASEPROJECTILE_H_
