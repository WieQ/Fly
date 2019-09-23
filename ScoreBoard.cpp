#include "pch.h"
#include "ScoreBoard.h"
#include <string>
#include <sstream>
#include <iostream>

ScoreBoard::ScoreBoard(int l, int sc, int st, int p) :lives(l),score(sc),stage(st),power(p)
{
	SetNumbers();
}

void ScoreBoard::SetNumbers()
{
	std::string path[2]{ "Numbers/",".png" };
	std::string convert_string_to_texture;
	std::stringstream convert_int_to_string;

	convert_int_to_string << lives;
	convert_int_to_string >> convert_string_to_texture;
	
	Tlives.resize(convert_string_to_texture.size());
	Slives.resize(convert_string_to_texture.size());

	for (int i = 0; i < Tlives.size(); ++i)
	{
		Tlives[i].loadFromFile(path[0] + convert_string_to_texture[i] + path[1]);
		Slives[i].setTexture(Tlives[i]);
		Slives[i].setScale(2, 2);
		Slives[i].setPosition(563+(10*i), 404);
	}
	convert_int_to_string.clear();
	convert_int_to_string << score;
	convert_int_to_string >> convert_string_to_texture;
	Tscore.resize(convert_string_to_texture.size());
	Sscore.resize(convert_string_to_texture.size());
	for (int i = 0; i < Tscore.size(); ++i)
	{
		Tscore[i].loadFromFile(path[0] + convert_string_to_texture[i] + path[1]);
		Sscore[i].setTexture(Tscore[i]);
		Sscore[i].setScale(2, 2);
		Sscore[i].setPosition(563 + (10 * i), 332);
	}

	convert_int_to_string.clear();
	convert_int_to_string << stage;
	convert_int_to_string >> convert_string_to_texture;
	Tstage.resize(convert_string_to_texture.size());
	Sstage.resize(convert_string_to_texture.size());
	for (int i = 0; i < Tstage.size(); ++i)
	{
		Tstage[i].loadFromFile(path[0] + convert_string_to_texture[i] + path[1]);
		Sstage[i].setTexture(Tstage[i]);
		Sstage[i].setScale(2, 2);
		Sstage[i].setPosition(563 + (10 * i), 296);
	}

	convert_int_to_string.clear();
	convert_int_to_string << power;
	convert_int_to_string >> convert_string_to_texture;
	Tpower.resize(convert_string_to_texture.size());
	Spower.resize(convert_string_to_texture.size());
	for (int i = 0; i < Tpower.size(); ++i)
	{
		Tpower[i].loadFromFile(path[0] + convert_string_to_texture[i] + path[1]);
		Spower[i].setTexture(Tpower[i]);
		Spower[i].setScale(2, 2);
		Spower[i].setPosition(563 + (10 * i), 368);
	}
	convert_int_to_string.clear();
}

void ScoreBoard::Tick()
{
	SetNumbers();
}

void ScoreBoard::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	for (size_t i = 0; i < Sscore.size(); ++i)
		target.draw(Sscore[i]);

	for (size_t i = 0; i < Sstage.size(); ++i)
		target.draw(Sstage[i]);

	for (size_t i = 0; i < Spower.size(); ++i)
		target.draw(Spower[i]);

	for (size_t i = 0; i < Slives.size(); ++i)
		target.draw(Slives[i]);
}