#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "OneStopEnemy.h"
#include "Boss1.h"
#include <cstdlib>
#include <ctime>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Time time1 = clock.getElapsedTime();
	int time2;
	sf::Texture HUD;
	HUD.loadFromFile("BackGround/HUD.png");
	sf::Sprite SHUD;
	SHUD.setTexture(HUD);
	SHUD.setScale(2, 2);
	sf::Texture bg;
	bg.loadFromFile("BackGround/bg.png");
	sf::Sprite Sbg;
	Sbg.setTexture(bg);
	Sbg.setOrigin(199, 351);
	Sbg.setPosition(250, 400);
	sf::Texture BossHP;
	sf::Sprite BossSHP;
	BossHP.loadFromFile("Boss/1/BossHP.png");
	BossSHP.setTexture(BossHP);
	BossSHP.setPosition(51, 40);
	Character Hime(Sbg.getGlobalBounds());

	std::vector<BaseEnemy*> enemies;
	//random device
	srand(time(NULL));
	Boss1 * S1Boss = nullptr;
	
	unsigned int temp_phase;

	while (window.isOpen())
	{
		
			time2 = clock.getElapsedTime().asSeconds();
			
			if (S1Boss != nullptr)
			{
				S1Boss->Tick(Hime.GetCharacterPos());
				Hime.Tick(sf::Vector2f(S1Boss->GetCurrentPosition()));
				if (Hime.shotcollision(S1Boss->GetCollision()))
				{
					S1Boss->Damage(10);
					BossSHP.setScale(S1Boss->GetHealth() /20 , 1);
				}

				if (S1Boss->ShotCollision(Hime.GetHitbox()))
					Hime.Damage();
			}
			else
				Hime.Tick(sf::Vector2f(0.0f,0.0f));
			for (unsigned int i = 0; i < enemies.size(); ++i)
			{
				if (enemies[i] != nullptr)
				{
					enemies[i]->Tick(Hime.GetCharacterPos());
					if (enemies[i]->ShotCollision(Hime.GetHitbox()) || Hime.charactercollision(enemies[i]->GetCollision()))
						Hime.Damage();
					if (Hime.shotcollision(enemies[i]->GetCollision()))
					{
						enemies[i]->Damage(1);
					}

				}
			}
			
			switch (time2)
			{
			case 0:
				for (unsigned int i = 0; i < enemies.size(); i++)
				{
					if (enemies[i] != nullptr)
						delete enemies[i];
				}
				temp_phase = 3;
				enemies.resize(11);
				for (unsigned int i = 0; i < temp_phase; i++)
				{
					enemies[i] = new BaseEnemy("Enemy/enemy2.png",sf::Vector2<float>(10.0f - (50 * i), 100.0f),sf::Vector2f(500.0f,300.0f) , Sbg.getGlobalBounds(), 20,2, 1);
				}	
				break;
			case 3:
				temp_phase = 6;
				for (unsigned int i = 3; i < temp_phase; i++)
				{
					enemies[i] = new BaseEnemy("Enemy/enemy2.png", sf::Vector2<float>(400.0f + (50 * i), 100.0f), sf::Vector2f(10.0f, 300.0f), Sbg.getGlobalBounds(), 20, 2, 1);
				}
			case 8:
				for (unsigned int i = 0; temp_phase < enemies.size(); i++)
				{
					if (enemies[temp_phase] != nullptr)
						delete enemies[temp_phase];
					enemies[temp_phase++] = new OneStopEnemy("Enemy/enemy2.png",sf::Vector2<float>(100.0f + (75 * i), 0.0f), sf::Vector2<float>(100.0f + (75 * i), 200.0f), sf::Vector2<float>(250, 0.0f), Sbg.getGlobalBounds(), 20, 1, 2);
				}
				break;
			case 14:
				for (unsigned int i = 0; i < enemies.size(); i++)
				{
					if (enemies[i] != nullptr)
						delete enemies[i];
				}
				enemies.resize(2);
				temp_phase = 2;
				for (unsigned int i = 0; i < temp_phase; i++)
				{
					enemies[i] = new OneStopEnemy("Enemy/enemy2.png",sf::Vector2<float>(100.0f + ( 300 * i), 0.0f), sf::Vector2<float>(400.0f - (300 * i), 200.0f), sf::Vector2<float>(400.0f - (300 * i), 0.0f), Sbg.getGlobalBounds(), 20,2, 2);
				}
				break;
			case 30:
				S1Boss = new Boss1(Sbg.getGlobalBounds());
				BossSHP.setScale(S1Boss->GetHealth()/20,1);
				break;
			default:
				break;
				
			}
			

			//std::cout << time1.asMicroseconds() << std::endl;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		
		window.clear();
		window.draw(Sbg);
		window.draw(Hime);
		if(S1Boss != nullptr)
			window.draw(*S1Boss);
		for (unsigned int i = 0; i < enemies.size(); ++i)
			if(enemies[i] != nullptr)
				window.draw(*enemies[i]);
		window.draw(SHUD);
		if (S1Boss != nullptr)
			window.draw(BossSHP);
		window.display();
	}

	return 0;
}
