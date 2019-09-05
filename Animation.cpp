#include "pch.h"
#include "Animation.h"
#include <sstream>

Animation::Animation(std::string p, std::string t1, unsigned short n) :pathtotexture(p),whichtexture(t1),PNG(".png")
{	
	frame = 0;
	count = 0;
	numberoftexture = n;
	frames = new int[numberoftexture];
	if (numberoftexture > 0)
		texture.loadFromFile(pathtotexture + whichtexture + PNG);
	Sprite.setTexture(texture);
}

void Animation::Tick()
{
	if (frame++ == frames[count])
	{
		if (count < numberoftexture)
		{
			count++;
			frame = 0;
		}
		else
		{
			count = 0;
			frame = 0;
		}

		if (count > 0)
		{
			std::stringstream ss;
			ss << count;
			std::string tempnumber;
			ss >> tempnumber;
			texture.loadFromFile(pathtotexture + whichtexture + tempnumber + PNG);
		}
		else
			texture.loadFromFile(pathtotexture + whichtexture + PNG);
	}
}

void Animation::SetFrame(int which [], unsigned short size)
{
	if (numberoftexture > size)
	{
		unsigned short i = 0;
		for (; i < size; ++i)
			frames[i] = which[i];

		for (i; i < numberoftexture; ++i)
			frames[i] = 0;
	}
	else
	{
		for (unsigned short i = 0; i < numberoftexture; ++i)
			frames[i] = which[i];		
	}
}

sf::Sprite& Animation::GetSprite() 
{
	return Sprite;
}