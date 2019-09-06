#pragma once
#ifndef BOSS1_H_
#define BOSS1_H_

#include "SinusProjectile.h"
#include "SFML/Graphics.hpp"
#include "SFML//System/Vector2.hpp"

class Boss1 : public sf::Drawable
{
	private:
		sf::Vector2<float> moving;
		sf::Vector2<float> startpoint;
		sf::Vector2<float> currentposition;
		sf::Vector2f road;
		sf::Vector2f road_speed;
		sf::Vector2f shot_target;
		// for Line movement
		float m;
		sf::Texture TBoss;
		sf::FloatRect world;
		sf::Sprite SBoss;
	

		std::vector<BaseProjectile*> pro;

		unsigned int ProCount;
		unsigned int MaxCount;
		int cd;
		int cd2;
		int Health;
		int next_path;
	
		short status;
		short series;
		short shoot_type;
		short path;
		

		float speed;

		bool alive;
	public:
		Boss1(sf::FloatRect w);
		~Boss1();
		void Tick(sf::Vector2f T);
		
		Boss1 operator=(Boss1 e1) {};
		sf::FloatRect GetCollision() { return SBoss.getGlobalBounds(); }
		sf::Vector2f GetCurrentPosition() { return currentposition; }
		void Damage(int D);
		bool ShotCollision(sf::FloatRect target);
		int GetHealth() { return Health; }
private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		void setMovement(sf::Vector2f);
		void shoting_1_stage();
		void shoting_2_stage();
		bool ReachedGoal();
		void Moving();
		
};
#endif // !BOSS1_H_
