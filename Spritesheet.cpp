#pragma once
#include "Settings.h"
#include "Spritesheet.h"

IntRect Spritesheet::GetSpriteArea(int i)
{
	int x = i%glyphs_x_;
	int y = i/glyphs_y_;
	return IntRect(
		x * settings::TILE_WIDTH,
		y * settings::TILE_WIDTH,
			settings::TILE_WIDTH,
			settings::TILE_WIDTH);
}

Spritesheet::Spritesheet(Texture* texture)
{
	sheet_ = texture;	
	sprite_.setTexture(*texture);
	glyphs_x_ = texture->getSize().x / settings::TILE_WIDTH;
	glyphs_y_ = texture->getSize().y / settings::TILE_WIDTH;
}

Sprite& Spritesheet::GetSprite(unsigned __int8 i)
{
	sprite_.setTextureRect(GetSpriteArea(i));
	return sprite_;
}
