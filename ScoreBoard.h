#pragma once
#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_
#include "SFML/Graphics.hpp"

class ScoreBoard : public sf::Drawable
{
	int lives;
	int score;
	int stage;
	int power;
	
	std::vector<sf::Texture> Tlives;
	std::vector<sf::Texture> Tscore;
	std::vector<sf::Texture> Tstage;
	std::vector<sf::Texture> Tpower;

	std::vector<sf::Sprite> Slives;
	std::vector<sf::Sprite> Sscore;
	std::vector<sf::Sprite> Sstage;
	std::vector<sf::Sprite> Spower;

	void SetNumbers();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
public:
	ScoreBoard(int l = 0, int sc = 0, int st = 0, int p = 0);
	~ScoreBoard() {};
	void Tick();
	void setLives(int l) { lives = l; };
	void setScore(int sc) { score = sc; };
	void setStage(int st) { stage = st; };
	void setPower(int p) { power = p; };
};
#endif // !SCOREBOARD_H_
