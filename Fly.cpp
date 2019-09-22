#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "OneStopEnemy.h"
#include "MedusaEnemy.h"
#include "Boss1.h"
#include <cstdlib>
#include <ctime>
#include "PowerUp.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Fly");
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Time time1 = clock.getElapsedTime();
	int stage_timer;
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
	//
	sf::Texture BossHP;
	sf::Sprite BossSHP;
	BossHP.loadFromFile("Boss/1/BossHP.png");
	BossSHP.setTexture(BossHP);
	BossSHP.setPosition(51, 40);
	//
	Character Hime(Sbg.getGlobalBounds());
	//
	std::vector<BaseEnemy*> enemies;
	std::vector<BaseEnemy*> enemies2;
	//
	std::vector<PowerUp*> powerup;
	std::vector<PowerUp*> powerup2;
	//
	int PowerUpcount = 0;
	int PowerUpcount2 = 0;
	//random device
	srand(time(NULL));
	Boss1 * S1Boss = nullptr;
	unsigned int temp_phase;
	bool next_enemies;
	int previous_timer = -1;
	while (window.isOpen())
	{
			stage_timer = clock.getElapsedTime().asSeconds();
			if (stage_timer != previous_timer)
			{
				next_enemies = true;
				previous_timer = stage_timer;
			}
			if (S1Boss != nullptr)
			{
				S1Boss->Tick(Hime.GetCharacterPos());
				Hime.Tick(sf::Vector2f(S1Boss->GetCurrentPosition()));
				if (Hime.shotcollision(S1Boss->GetCollision()))
				{
					S1Boss->Damage(Hime.GetDamage());
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
						if (enemies[i]->Damage(Hime.GetDamage()))
						{
							if (rand() % 3 + 1 == 1)
							{
								if (powerup[PowerUpcount] != nullptr)
									delete powerup[PowerUpcount];
								powerup[PowerUpcount++] = new PowerUp(enemies[i]->GetPosition());
							}
						}

				}
			}
			for (unsigned int i = 0; i < enemies2.size(); ++i)
			{
				if (enemies2[i] != nullptr)
				{
					enemies2[i]->Tick(Hime.GetCharacterPos());
					if (enemies2[i]->ShotCollision(Hime.GetHitbox()) || Hime.charactercollision(enemies[i]->GetCollision()))
						Hime.Damage();
					if (Hime.shotcollision(enemies2[i]->GetCollision()))
						if (enemies2[i]->Damage(Hime.GetDamage())) 
						{
							if (rand() % 3 + 1 == 1)
							{
								if (powerup2[PowerUpcount2] != nullptr)
									delete powerup2[PowerUpcount2];
								powerup2[PowerUpcount2++] = new PowerUp(enemies2[i]->GetPosition());
							}
						}

				}
			}
			for (unsigned int i = 0; i < powerup.size(); ++i)
			{
				if (powerup[i] != nullptr)
				{
					powerup[i]->Tick();
					if (powerup[i]->CharacterCollision(Hime.GetCurrentSprite().getGlobalBounds()))
					{
						Hime.incDMG();
						delete powerup[i];
						powerup[i] = nullptr;
					}
				}
			}
			for (unsigned int i = 0; i < powerup2.size(); ++i)
			{
				if (powerup2[i] != nullptr)
				{
					powerup2[i]->Tick();
					if (powerup2[i]->CharacterCollision(Hime.GetCurrentSprite().getGlobalBounds()))
					{
						Hime.incDMG();
						delete powerup2[i];
						powerup2[i] = nullptr;
					}
				}
			}
	
			switch (stage_timer)
			{
			case 0:
				if (next_enemies)
				{
					for (unsigned int i = 0; i < enemies.size(); i++)
					{
						if (enemies[i] != nullptr)
							delete enemies[i];
						if (powerup[i] != nullptr)
							delete powerup[i];
					}
					temp_phase = 3;
					enemies.resize(11);
					powerup.resize(11);
					PowerUpcount = 0;
					for (unsigned int i = 0; i < temp_phase; i++)
					{
						enemies[i] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(10.0f - (50 * i), 100.0f), sf::Vector2f(500.0f, 300.0f), Sbg.getGlobalBounds(), 50, 3, 0);
					}
					next_enemies = false;
				}
				break;

			case 3:
				if (next_enemies)
				{
					temp_phase = 6;
					for (unsigned int i = 3; i < temp_phase; i++)
					{
						enemies[i] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(400.0f + (50 * i), 100.0f), sf::Vector2f(10.0f, 300.0f), Sbg.getGlobalBounds(), 50, 3, 0);
					}
					next_enemies = false;
				}
				break;
			case 8:
				if (next_enemies)
				{
					for (unsigned int i = 0; temp_phase < enemies.size(); i++)
					{
						if (enemies[temp_phase] != nullptr)
							delete enemies[temp_phase];
						enemies[temp_phase++] = new OneStopEnemy("Enemy/enemy2.png", sf::Vector2<float>(100.0f + (75 * i), 0.0f), sf::Vector2<float>(100.0f + (75 * i), 200.0f), sf::Vector2<float>(250, 0.0f), Sbg.getGlobalBounds(), 50, 1, 2);
					}
					next_enemies = false;
				}
				break;


			case 10:
				if (next_enemies)
				{
					enemies2.resize(10);
					powerup2.resize(10);
					for (unsigned int i = 0; i < enemies2.size(); i++)
					{
						if (enemies2[i] != nullptr)
							delete enemies2[i];
						if (powerup2[i] != nullptr)
							delete powerup2[i];
						enemies2[i] = nullptr;
						powerup2[i] = nullptr;
					}

					PowerUpcount2 = 0;
					temp_phase = 2;
					for (unsigned int i = 0; i < temp_phase; i++)
					{
						enemies2[i] = new OneStopEnemy("Enemy/enemy2.png", sf::Vector2<float>(100.0f + (300 * i), 0.0f), sf::Vector2<float>(400.0f - (300 * i), 200.0f), sf::Vector2<float>(400.0f - (300 * i), 0.0f), Sbg.getGlobalBounds(), 50, 2, 2);

					}
					next_enemies = false;
				}
				break;
			case 13:
				if (next_enemies)
				{
					for (int i = 0; temp_phase < enemies2.size(); ++i)
					{
						if (i % 2 == 0)
							enemies2[temp_phase++] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(500.0f + (50 * i), 100.0f), sf::Vector2f(100.0f, 600.0f), Sbg.getGlobalBounds(), 50, 3, 0);
						else
							enemies2[temp_phase++] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(10.0f - (50 * i), 100.0f), sf::Vector2f(400.0f, 600.0f), Sbg.getGlobalBounds(), 50, 3, 0);
					}
					next_enemies = false;
				}

				break;

			case 20:
				if (next_enemies) 
				{
					for (unsigned int i = 0; i < enemies.size(); i++)
					{
						if (enemies[i] != nullptr)
							delete enemies[i];
						if (powerup[i] != nullptr)
							delete powerup[i];
					}
					enemies.resize(10);
					powerup.resize(10);
					PowerUpcount = 0;
					for (unsigned int i = 0; i < enemies.size(); i++)
					{
						enemies[i] = new OneStopEnemy("Enemy/enemy2.png", sf::Vector2<float>(100.0f + (30 * i), 0.0f - (150 * i)), sf::Vector2<float>(100.0f + (30 * i), 150.0f), sf::Vector2<float>(100.0f + (30.0f *i), 0.0f), Sbg.getGlobalBounds(), 50, 2, 2);
						powerup[i] = nullptr;

					}
					next_enemies = false;
				}
				break;


			case 25:
				if (next_enemies)
				{
					for (unsigned int i = 0; i < enemies2.size(); i++)
					{
						if (enemies2[i] != nullptr)
							delete enemies2[i];
						if (powerup2[i] != nullptr)
							delete powerup2[i];
						enemies2[i] = nullptr;
						powerup2[i] = nullptr;
					}
					enemies2.resize(6);
					powerup2.resize(6);
					temp_phase = 0;
					PowerUpcount2 = 0;
					for (int i = 0; i < 2; i++)
					{
						if (i % 2 == 0)
							enemies2[temp_phase++] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(500.0f, 100.0f), Hime.GetCharacterPos(), Sbg.getGlobalBounds(), 50, 3, 1);
						else
							enemies2[temp_phase++] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(10.0f, 100.0f), Hime.GetCharacterPos(), Sbg.getGlobalBounds(), 50, 3, 1);
					}
					next_enemies = false;
				}
				break;

			case 30:
				if (next_enemies)
				{
					for (int i = 0; i < 2; i++)
					{
						std::cout << i << std::endl;
						if (i % 2 == 0)
						{
							enemies2[temp_phase++] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(500.0f, 100.0f), Hime.GetCharacterPos(), Sbg.getGlobalBounds(), 50, 3, 1);
						}
						else
						{
							enemies2[temp_phase++] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(10.0f, 100.0f), Hime.GetCharacterPos(), Sbg.getGlobalBounds(), 50, 3, 1);
						}

					}
					next_enemies = false;
				}
				break;
			case 35:
				if (next_enemies)  
				{
					for (int i = 0; i < 2; i++)
					{
						if (temp_phase < enemies2.size())
						{
							if (i % 2 == 0)
								enemies2[temp_phase++] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(500.0f, 100.0f), Hime.GetCharacterPos(), Sbg.getGlobalBounds(), 50, 3, 1);
							else
								enemies2[temp_phase++] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(10.0f, 100.0f), Hime.GetCharacterPos(), Sbg.getGlobalBounds(), 50, 3, 1);
						}

					}
					next_enemies = false;
				}
			break;
			case 40:
				if (next_enemies)
				{
					S1Boss = new Boss1(Sbg.getGlobalBounds());
					BossSHP.setScale(S1Boss->GetHealth() / 20, 1);
					next_enemies = false;
				}
				break;

			}

		//std::cout << stage_timer << std::endl;
		std::cout << temp_phase << std::endl;


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

	//drawing enemies 
		for (unsigned int i = 0; i < enemies.size(); ++i)
			if(enemies[i] != nullptr)
				window.draw(*enemies[i]);
		for (unsigned int i = 0; i < enemies2.size(); ++i)
			if (enemies2[i] != nullptr)
				window.draw(*enemies2[i]);

	//drawing PowerUps
		for (unsigned int i = 0; i < powerup.size(); ++i)
			if (powerup[i] != nullptr)
				window.draw(*powerup[i]);
		for (unsigned int i = 0; i < powerup2.size(); ++i)
			if (powerup2[i] != nullptr)
				window.draw(*powerup2[i]);

		window.draw(SHUD);
		if (S1Boss != nullptr)
			window.draw(BossSHP);
		window.display();
	}

	return 0;
}
