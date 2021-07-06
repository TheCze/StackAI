#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Settings.h"

using namespace sf;

class Spritesheet{
private:
	Texture* sheet_=nullptr;
	Sprite sprite_;
	int glyphs_x_=0;
	int glyphs_y_=0;
	IntRect GetSpriteArea(int i);
public:
	Spritesheet(Texture* texture);
	Sprite& GetSprite(unsigned __int8 i);
};


