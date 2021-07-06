#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Settings.h"

using namespace sf;

class Spritesheet{
private:
	Texture* m_sheet=nullptr;
	Sprite m_sprite;
	int m_glyphs_x=0;
	int m_glyphs_y=0;
	IntRect getSpriteArea(int i);
public:
	Spritesheet(Texture* texture);
	Sprite& getSprite(unsigned __int8 i);
};


