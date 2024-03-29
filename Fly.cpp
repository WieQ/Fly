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
#include "ScoreBoard.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Fly");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(1);
	int menu_case = 1;
	sf::Texture Menu;
	sf::Texture Play;
	sf::Texture Exit;
	sf::Texture Setti;

	sf::Sprite SMenu;
	sf::Sprite SPlay;
	sf::Sprite SExit;
	sf::Sprite SSetti;

	sf::Event event;
	Menu.loadFromFile("Menu/Menu.png");
	SMenu.setTexture(Menu);
	SMenu.setScale(2, 2);

	Play.loadFromFile("Menu/Play.png");
	SPlay.setTexture(Play);
	SPlay.setPosition(365.0f, 360.0f);

	Exit.loadFromFile("Menu/Exit.png");
	SExit.setTexture(Exit);
	SExit.setPosition(365.0f, 500.0f);

	Setti.loadFromFile("Menu/Setti.png");
	SSetti.setTexture(Setti);
	SSetti.setPosition(365.0f, 430.0f);
	
	int KeyCd = 0;

	while (window.isOpen())
	{
		if (KeyCd-- < 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				menu_case--;
				if (menu_case < 1)
					menu_case = 3;
				KeyCd = 10;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				menu_case++;
				if (menu_case > 3)
					menu_case = 1;
				KeyCd = 10;
			}
			
		}
		switch (menu_case)
		{
		case 1:
			Play.loadFromFile("Menu/Play2.png");
			Exit.loadFromFile("Menu/Exit.png");
			Setti.loadFromFile("Menu/Setti.png");
			break;
		case 2:
			Play.loadFromFile("Menu/Play.png");
			Exit.loadFromFile("Menu/Exit.png");
			Setti.loadFromFile("Menu/Setti2.png");
			break;
		case 3:
			Play.loadFromFile("Menu/Play.png");
			Exit.loadFromFile("Menu/Exit2.png");
			Setti.loadFromFile("Menu/Setti.png");
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			switch (menu_case)
			{
			case 1:
			{
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
				ScoreBoard sb;
				//
				int PowerUpcount = 0;
				int PowerUpcount2 = 0;
				//random device
				srand(time(NULL));
				Boss1 * S1Boss = nullptr;
				unsigned int temp_phase;
				bool next_enemies;
				int previous_timer = -1;
				int score = 1;
				int x = sf::Style::Fullscreen;
				while (Hime.Getlives() != 0)
				{
					sb.setLives(Hime.Getlives());
					sb.setPower(Hime.GetDamage());

					sb.setScore(score);
					sb.setStage(1);
					sb.Tick();
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
							score++;
							BossSHP.setScale(S1Boss->GetHealth() / 20, 1);
						}

						if (S1Boss->ShotCollision(Hime.GetHitbox()))
							if (Hime.Damage())
							{
								if (score > 10)
									score -= 10;
								else
									score = 0;
							}
					}
					else
						Hime.Tick(sf::Vector2f(0.0f, 0.0f));
					for (unsigned int i = 0; i < enemies.size(); ++i)
					{
						if (enemies[i] != nullptr)
						{
							enemies[i]->Tick(Hime.GetCharacterPos());
							if (enemies[i]->ShotCollision(Hime.GetHitbox()) || Hime.charactercollision(enemies[i]->GetCollision()))
								if (Hime.Damage())
								{
									if (score > 10)
										score -= 10;
									else
										score = 0;
								}
							if (Hime.shotcollision(enemies[i]->GetCollision()))
							{
								++score;
								if (enemies[i]->Damage(Hime.GetDamage()))
								{
									if (rand() % 2 + 1 == 1)
									{
										if (powerup[PowerUpcount] != nullptr)
											delete powerup[PowerUpcount];
										powerup[PowerUpcount++] = new PowerUp(enemies[i]->GetPosition());
									}
								}
							}

						}
					}
					for (unsigned int i = 0; i < enemies2.size(); ++i)
					{
						if (enemies2[i] != nullptr)
						{
							enemies2[i]->Tick(Hime.GetCharacterPos());
							if (enemies2[i]->ShotCollision(Hime.GetHitbox()) || Hime.charactercollision(enemies2[i]->GetCollision()))
								if (Hime.Damage())
								{
									if (score > 10)
										score -= 10;
									else
										score = 0;
								}
							if (Hime.shotcollision(enemies2[i]->GetCollision()))
							{
								++score;
								if (enemies2[i]->Damage(Hime.GetDamage()))
								{
									if (rand() % 2 + 1 == 1)
									{
										if (powerup2[PowerUpcount2] != nullptr)
											delete powerup2[PowerUpcount2];
										powerup2[PowerUpcount2++] = new PowerUp(enemies2[i]->GetPosition());
									}
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
								score += 5;
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
								score += 5;
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
							enemies.resize(9);
							powerup.resize(9);
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
								enemies[temp_phase++] = new OneStopEnemy("Enemy/enemy2.png", sf::Vector2<float>(100.0f + (150 * i), 0.0f), sf::Vector2<float>(100.0f + (150 * i), 200.0f), sf::Vector2<float>(250, 0.0f), Sbg.getGlobalBounds(), 50, 1, 2);
							}
							next_enemies = false;
						}
						break;


					case 10:
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
							enemies2.resize(10);
							powerup2.resize(10);
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
									enemies2[temp_phase] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(500.0f + (50 * i), 100.0f), sf::Vector2f(100.0f, 600.0f), Sbg.getGlobalBounds(), 50, 3, 0);
								else
									enemies2[temp_phase] = new MedusaEnemy("Enemy/NMedusa/1.png", sf::Vector2<float>(10.0f - (50 * i), 100.0f), sf::Vector2f(400.0f, 600.0f), Sbg.getGlobalBounds(), 50, 3, 0);
								temp_phase++;
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

					default:
						break;
					}

					
					window.clear();
					window.draw(Sbg);
					window.draw(Hime);
					if (S1Boss != nullptr)
						window.draw(*S1Boss);

					//drawing enemies 
					for (unsigned int i = 0; i < enemies.size(); ++i)
						if (enemies[i] != nullptr)
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
					window.draw(sb);
					window.display();
					
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
						{
							window.close();
							return 1;
						}
					}
				}
				for (int i = 0; i < enemies.size(); ++i)
					if (enemies[i] != nullptr)
						delete enemies[i];
				for (int i = 0; i < enemies2.size(); ++i)
					if (enemies2[i] != nullptr)
						delete enemies2[i];
				for (int i = 0; i < powerup.size(); ++i)
					if (powerup[i] != nullptr)
						delete powerup[i];
				for (int i = 0; i < powerup2.size(); ++i)
					if (powerup2[i] != nullptr)
						delete powerup2[i];
				if (S1Boss != nullptr)
					delete S1Boss;
			}
			
			break;
			case 2:
				break;
			case 3:
				window.close();
				break;
			}
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
			
			window.clear();
			
			window.draw(SMenu);
			window.draw(SPlay);
			window.draw(SExit);
			window.draw(SSetti);
			window.display();
	}
		

	return 0;
}
