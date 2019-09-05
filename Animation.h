#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"
#include <string>

class Animation
{
private:
	int count;
	int frame;
	int* frames;
	const std::string PNG;
	unsigned short numberoftexture;
	std::string whichtexture;
	std::string pathtotexture;
	sf::Texture texture;
	sf::Sprite Sprite;
public:
	Animation(std::string p, std::string t1, unsigned short n);
	void Tick();
	void SetFrame(int which [], unsigned short size);
	sf::Sprite& GetSprite();
};