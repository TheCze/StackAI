#pragma once
#include "Settings.h"
#include "Spritesheet.h"

IntRect Spritesheet::getSpriteArea(int i)
{
	int x = i%m_glyphs_x;
	int y = i/m_glyphs_y;
	return IntRect(
		x * settings::TILE_WIDTH,
		y * settings::TILE_WIDTH,
			settings::TILE_WIDTH,
			settings::TILE_WIDTH);
}

Spritesheet::Spritesheet(Texture* texture)
{
	m_sheet = texture;	
	m_sprite.setTexture(*texture);
	m_glyphs_x = texture->getSize().x / settings::TILE_WIDTH;
	m_glyphs_y = texture->getSize().y / settings::TILE_WIDTH;
}

Sprite& Spritesheet::getSprite(unsigned __int8 i)
{
	m_sprite.setTextureRect(getSpriteArea(i));
	return m_sprite;
}
